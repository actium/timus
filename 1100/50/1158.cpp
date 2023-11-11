#include <iostream>
#include <deque>
#include <string>
#include <vector>

#include <cassert>
#include <cstdint>

namespace long_arithmetic {

    class integer {
        using storage_type = std::vector<uint32_t>;

    public:
        integer()
            : digits_(1)
        {}

        template <typename T>
        integer(T value)
        {
            for (size_t i = 0; i < (sizeof(T) + sizeof(uint32_t) - 1) / sizeof(uint32_t); ++i) {
                digits_.push_back(value);
                value >>= 32;
            }

            if constexpr (std::is_signed_v<T>)
                return;

            if (digits_.back() >= uint32_t(1) << 31)
                digits_.push_back(0);
        }

        integer& operator +=(const integer& rhs)
        {
            extend_sign(digits_, std::max(digits_.size(), rhs.digits_.size()) + 1);
            add(digits_, rhs.digits_);
            drop_redundant_sign_extension(digits_);
            return *this;
        }

        bool operator ==(const integer& rhs) const
        {
            const size_t n = digits_.size();
            if (rhs.digits_.size() != n)
                return false;

            if (static_cast<int32_t>(digits_.back() ^ rhs.digits_.back()) < 0)
                return false;

            for (size_t i = 0; i < n; ++i) {
                if (digits_[i] != rhs.digits_[i])
                    return false;
            }
            return true;
        }

        explicit operator std::string() const
        {
            storage_type digits = digits_;
            if (is_negative(digits_))
                negate(digits);

            std::string value;
            do {
                uint64_t carry = 0;
                for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
                    carry <<= 32;
                    carry += *it;
                    *it = carry / 1000000000;
                    carry %= 1000000000;
                }

                for (size_t i = 0; i < 9; ++i) {
                    value.push_back('0' + carry % 10);
                    carry /= 10;
                }

                drop_redundant_sign_extension(digits);
            } while (digits.size() > 1 || digits[0] != 0);

            while (value.length() > 1 && value.back() == '0')
                value.pop_back();

            if (is_negative(digits_))
                value.push_back('-');

            for (int i = 0, j = value.size() - 1; i < j; ++i, --j)
                std::swap(value[i], value[j]);

            return value;
        }

    private:
        explicit integer(storage_type digits)
            : digits_(std::move(digits))
        {}

        static bool is_negative(const storage_type& digits)
        {
            return static_cast<int32_t>(digits.back()) < 0;
        }

        static void extend_sign(storage_type& digits, size_t target_size)
        {
            digits.resize(target_size, is_negative(digits) ? ~uint32_t(0) : 0);
        }

        static void drop_redundant_sign_extension(storage_type& digits)
        {
            for (size_t n = digits.size(); n > 1; --n) {
                if (digits.back() != 0 && digits.back() != ~uint32_t(0))
                    break;

                if (static_cast<int32_t>(digits[n-2] ^ digits[n-1]) < 0)
                    break;

                digits.pop_back();
            }
        }

        static void negate(storage_type& digits)
        {
            extend_sign(digits, digits.size() + 1);

            uint64_t carry = 1;
            for (auto it = digits.begin(); it != digits.end(); ++it) {
                carry += ~*it;
                *it = carry;
                carry >>= 32;
            }

            drop_redundant_sign_extension(digits);
        }

        template <typename F>
        static void add(storage_type& lhs, size_t rhs_size, uint32_t rhs_sign_extension, F&& rhs_getter, unsigned delta)
        {
            assert(lhs.size() >= rhs_size);

            uint64_t sum = delta;
            for (size_t i = 0; i < rhs_size; ++i) {
                sum += lhs[i];
                sum += rhs_getter(i);
                lhs[i] = sum;
                sum >>= 32;
            }

            for (size_t i = rhs_size; i < lhs.size(); ++i) {
                sum += lhs[i];
                sum += rhs_sign_extension;
                lhs[i] = sum;
                sum >>= 32;
            }
        }

        static void add(storage_type& lhs, const storage_type& rhs)
        {
            add(lhs, rhs.size(), is_negative(rhs) ? ~uint32_t(0) : 0, [&](size_t i) {
                return rhs[i];
            }, 0);
        }

    private:
        storage_type digits_;

    }; // class integer

    std::ostream& operator <<(std::ostream& output, const integer& value)
    {
        return output << static_cast<std::string>(value);
    }

} // namespace long_arithmetic

void simplify(std::vector<std::string>& words)
{
    size_t word_count = words.size();

    const auto check = [&](size_t i) {
        for (size_t j = 0; j < word_count; ++j) {
            if (j != i && words[i].find(words[j]) != std::string::npos)
                return true;
        }
        return false;
    };

    for (size_t i = 0; i < word_count; ++i) {
        if (check(i))
            words[i--] = std::move(words[--word_count]);
    }

    words.resize(word_count);
}

class Automaton {
    using integer = long_arithmetic::integer;

    struct Node {
        int parent;
        unsigned label;
        std::vector<int> next;
        std::vector<int> go;
        int link = -1;
        bool terminal = false;

        Node(unsigned alphabet_size, int parent, unsigned label)
            : parent(parent)
            , label(label)
            , next(alphabet_size, -1)
            , go(alphabet_size, -1)
        {}
    };

public:
    explicit Automaton(unsigned alphabet_size, const std::vector<std::string>& forbidden_words)
        : alphabet_size_(alphabet_size)
        , nodes_(1, Node(alphabet_size, -1, ~0u))
    {
        const size_t word_count = forbidden_words.size();

        for (size_t i = 0; i < word_count; ++i) {
            int v = 0;
            for (const char label : forbidden_words[i]) {
                if (nodes_[v].next[label] == -1) {
                    nodes_[v].next[label] = nodes_.size();
                    nodes_.emplace_back(alphabet_size, v, label);
                }
                v = nodes_[v].next[label];
            }
            nodes_[v].terminal = true;
        }
    }

    integer count_words(unsigned length)
    {
        const unsigned state_count = nodes_.size();

        std::vector<integer> counts(state_count);
        counts[0] = 1;
        for (unsigned i = 0; i < length; ++i) {
            std::vector<integer> next_counts(state_count + 1);
            for (unsigned j = 0; j < state_count; ++j) {
                if (counts[j] == 0)
                    continue;

                for (unsigned k = 0; k < alphabet_size_; ++k) {
                    const unsigned target_state = go(j, k);
                    if (!nodes_[target_state].terminal)
                        next_counts[target_state] += counts[j];
                }
            }
            counts = std::move(next_counts);
        }

        integer k = 0;
        for (unsigned i = 0; i < state_count; ++i)
            k += counts[i];

        return k;
    }

private:
    int get_link(int v)
    {
        if (nodes_[v].link == -1) {
            if (v == 0 || nodes_[v].parent == 0)
                nodes_[v].link = 0;
            else
                nodes_[v].link = go(get_link(nodes_[v].parent), nodes_[v].label);
        }
        return nodes_[v].link;
    }

    int go(int v, unsigned label)
    {
        if (nodes_[v].go[label] == -1) {
            if (nodes_[v].next[label] != -1)
                nodes_[v].go[label] = nodes_[v].next[label];
            else
                nodes_[v].go[label] = (v == 0 ? 0 : go(get_link(v), label));
        }
        return nodes_[v].go[label];
    }

private:
    const unsigned alphabet_size_;

    std::deque<Node> nodes_;

}; // class Automaton

long_arithmetic::integer solve(unsigned n, unsigned l, const std::vector<std::string>& words)
{
    return Automaton(l, words).count_words(n);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, k, l;
    std::cin >> l >> n >> k;

    std::string alphabet;
    std::cin >> alphabet;

    std::vector<std::string> words(k);
    for (unsigned i = 0; i < k; ++i) {
        std::cin >> words[i];

        for (char& c : words[i])
            c = alphabet.find(c);
    }

    simplify(words);

    std::cout << solve(n, l, words) << '\n';

    return 0;
}
