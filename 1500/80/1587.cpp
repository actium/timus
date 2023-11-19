#include <iostream>
#include <string>
#include <vector>

#include <cassert>
#include <cstdint>

namespace long_arithmetic {

    class integer {
        using storage_type = std::vector<uint32_t>;

    public:
        integer(int value)
        {
            digits_.push_back(value);
        }

        integer& operator *=(const integer& rhs)
        {
            storage_type product(digits_.size() + rhs.digits_.size() + 1);
            multiply(digits_, rhs.digits_, product);
            if (static_cast<int32_t>(digits_.back() ^ rhs.digits_.back()) < 0)
                negate(product);
            else
                drop_redundant_sign_extension(product);
            digits_.swap(product);
            return *this;
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

        int compare(const integer& rhs) const
        {
            const int32_t lms = digits_.end()[-1], rms = rhs.digits_.end()[-1];
            if ((lms ^ rms) < 0)
                return lms < 0 ? -1 : 1;

            if (digits_.size() != rhs.digits_.size())
                return (digits_.size() > rhs.digits_.size() && lms < 0)
                    || (digits_.size() < rhs.digits_.size() && rms >= 0) ? -1 : 1;

            for (size_t i = 1; i <= digits_.size(); ++i) {
                const int64_t lhs_digit = digits_.end()[-i], rhs_digit = rhs.digits_.end()[-i];
                if (lhs_digit != rhs_digit)
                    return lhs_digit - rhs_digit < 0 ? -1 : 1;
            }

            return 0;
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

        static void multiply(const storage_type& lhs, const storage_type& rhs, storage_type& product)
        {
            const size_t n = lhs.size(), m = rhs.size();

            uint64_t digit_l = is_negative(lhs);
            for (size_t i = 0; i < n; ++i) {
                digit_l += is_negative(lhs) ? ~lhs[i] : lhs[i];
                if (digit_l == 0)
                    continue;

                uint64_t digit_r = is_negative(rhs);
                for (size_t j = 0; j < m; ++j) {
                    digit_r += is_negative(rhs) ? ~rhs[j] : rhs[j];
                    if (digit_r == 0)
                        continue;

                    uint64_t p = static_cast<uint32_t>(digit_l);
                    p *= static_cast<uint32_t>(digit_r);

                    uint64_t c = static_cast<uint32_t>(p);
                    c += product[i+j];
                    product[i+j] = c;

                    c >>= 32;
                    c += p >> 32;
                    c += product[i+j+1];
                    product[i+j+1] = c;

                    product[i+j+2] += c >> 32;

                    digit_r >>= 32;
                }
                digit_l >>= 32;
            }
        }

    private:
        storage_type digits_;

    }; // class integer

    std::ostream& operator <<(std::ostream& output, const integer& value)
    {
        return output << static_cast<std::string>(value);
    }

    integer operator *(const integer& lhs, const integer& rhs)
    {
        return integer(lhs) *= rhs;
    }

    bool operator <(const integer& lhs, const integer& rhs)
    {
        return lhs.compare(rhs) < 0;
    }

} // namespace long_arithmetic

using long_arithmetic::integer;

integer solve(const std::vector<int>& v, size_t lb, size_t ub)
{
    if (lb + 1 == ub)
        return v[lb];

    std::vector<size_t> p;
    for (size_t i = lb; i < ub; ++i) {
        if (v[i] < 0)
            p.push_back(i);
    }

    const auto product = [&](size_t lb, size_t ub) {
        integer p = 1;
        for (size_t i = lb; i < ub; ++i)
            p *= v[i];

        return p;
    };

    if (p.size() % 2 == 0)
        return product(lb, ub);

    if (p.front() == lb)
        return product(lb + 1, ub);

    if (p.back() + 1 == ub)
        return product(lb, ub - 1);

    if (p.size() == 1)
        return std::max(product(lb, p.front()), product(p.front() + 1, ub));

    integer sp[3] = { product(lb, p.front()), product(p.front() + 1, p.back()), product(p.back() + 1, ub) };
    return std::max(sp[0] * v[p.front()] * sp[1], sp[1] * v[p.back()] * sp[2]);
}

integer solve(const std::vector<int>& v)
{
    const size_t n = v.size();

    std::vector<int> p;
    for (size_t i = 0; i < n; ++i) {
        if (v[i] == 0)
            p.push_back(i);
    }
    p.push_back(n);

    integer max = (p.size() == 1 ? v[0] : std::max(v[0], 0));
    {
        size_t x = 0;
        for (const size_t b : p) {
            if (b > x + 1)
                max = std::max<integer>(max, solve(v, x, b));

            x = b + 1;
        }
    }
    return max;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<int> v(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> v[i];

    std::cout << solve(v) << '\n';

    return 0;
}
