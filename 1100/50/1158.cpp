#include <iostream>
#include <deque>
#include <string>
#include <vector>

class Integer {
public:
    Integer()
        : Integer(0)
    {}

    Integer(unsigned value)
        : value_(std::to_string(value))
    {}

    Integer& operator +=(const Integer& rhs)
    {
        const size_t n = std::max(value_.length(), rhs.value_.length());

        value_.resize(n + 1, '0');
        for (size_t i = 0; i < rhs.value_.length(); ++i) {
            const unsigned d = (value_[i] - '0') + (rhs.value_[i] - '0');
            value_[i] = '0' + d % 10;
            value_[i+1] += d / 10;
        }
        for (size_t i = rhs.value_.length(); i < n && value_[i] > '9'; ++i) {
            value_[i] = '0';
            ++value_[i+1];
        }

        if (value_.back() == '0')
            value_.pop_back();

        return *this;
    }

    bool operator ==(const Integer& rhs) const
    {
        return value_ == rhs.value_;
    }

private:
    std::string value_;

    friend std::ostream& operator <<(std::ostream& output, const Integer& v)
    {
        return output << std::string(v.value_.rbegin(), v.value_.rend());
    }

}; // class Integer

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

    Integer count_words(unsigned length)
    {
        const unsigned state_count = nodes_.size();

        std::vector<Integer> counts(state_count);
        counts[0] = 1;
        for (unsigned i = 0; i < length; ++i) {
            std::vector<Integer> next_counts(state_count + 1);
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

        Integer k = 0;
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

Integer solve(unsigned n, unsigned l, const std::vector<std::string>& words)
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
