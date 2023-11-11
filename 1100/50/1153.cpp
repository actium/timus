#include <iostream>
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

        static integer parse(std::string_view value)
        {
            bool negative = false;
            if (value[0] == '-') {
                negative = true;
                value.remove_prefix(1);
            }

            storage_type digits;
            for ( ; !value.empty(); value.remove_prefix(1)) {
                uint64_t carry = value[0] - '0';
                for (auto it = digits.begin(); it != digits.end(); ++it) {
                    carry += static_cast<uint64_t>(*it) * 10;
                    *it = carry;
                    carry >>= 32;
                }
                digits.push_back(carry);

                drop_redundant_sign_extension(digits);
            }

            if (negative)
                negate(digits);

            return integer(std::move(digits));
        }

        integer& operator +=(const integer& rhs)
        {
            extend_sign(digits_, std::max(digits_.size(), rhs.digits_.size()) + 1);
            add(digits_, rhs.digits_);
            drop_redundant_sign_extension(digits_);
            return *this;
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

        integer& operator >>=(unsigned rhs)
        {
            const unsigned discarded_digit_count = rhs / 32;
            if (discarded_digit_count >= digits_.size()) {
                digits_.assign(1, is_negative(digits_) ? ~uint32_t(0) : 0);
            } else {
                digits_.erase(digits_.begin(), digits_.begin() + discarded_digit_count);
                discard_least_significant_bits(digits_, rhs % 32);
                drop_redundant_sign_extension(digits_);
            }
            return *this;
        }

        bool operator <(const integer& rhs) const
        {
            return compare(digits_, rhs.digits_) < 0;
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

        static void discard_least_significant_bits(storage_type& digits, unsigned bit_count)
        {
            if (bit_count == 0)
                return;

            const size_t size = digits.size();
            extend_sign(digits, size + 1);
            for (size_t i = 0; i < size; ++i) {
                digits[i] >>= bit_count;
                digits[i] |= digits[i+1] << (32 - bit_count);
            }
            digits.pop_back();
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

        static int compare(const storage_type& lhs, const storage_type& rhs)
        {
            const int32_t lmsb = lhs.back(), rmsb = rhs.back();
            if (static_cast<int32_t>(lhs.back() ^ rhs.back()) < 0)
                return lmsb < 0 ? -1 : 1;

            const size_t lsize = lhs.size(), rsize = rhs.size();
            if (lsize != rsize)
                return (lsize > rsize && lmsb < 0) || (lsize < rsize && rmsb >= 0) ? -1 : 1;

            for (size_t i = 1; i <= lsize; ++i) {
                if (lhs[lsize-i] != rhs[rsize-i])
                    return static_cast<int64_t>(lhs[lsize-i]) - static_cast<int64_t>(rhs[rsize-i]) < 0 ? -1 : 1;
            }
            return 0;
        }

    private:
        storage_type digits_;

    }; // class integer

    std::ostream& operator <<(std::ostream& output, const integer& value)
    {
        return output << static_cast<std::string>(value);
    }

    integer operator +(integer lhs, const integer& rhs)
    {
        return lhs += rhs;
    }

    integer operator *(integer lhs, const integer& rhs)
    {
        return lhs *= rhs;
    }

    integer operator >>(integer lhs, unsigned rhs)
    {
        return lhs >>= rhs;
    }

} // namespace long_arithmetic

using long_arithmetic::integer;

integer solve(const std::string& n)
{
    const integer x = 2 * integer::parse(n);

    integer lb = 0, ub = integer::parse("1" + std::string(n.length() / 2 + 1, '0'));
    while (lb + 1 < ub) {
        const integer mid = (lb + ub) >> 1;
        (x < mid * (mid + 1) ? ub : lb) = mid;
    }
    return lb;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    std::cout << solve(s) << '\n';

    return 0;
}
