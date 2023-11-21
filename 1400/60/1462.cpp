#include <iostream>
#include <string>
#include <vector>

#include <cstdint>

namespace long_arithmetic {

    class integer {
    public:
        integer(unsigned value)
        {
            digits_[digit_count_++] = value;
        }

        integer& operator +=(const integer& rhs)
        {
            const unsigned target_size = std::max(digit_count_, rhs.digit_count_) + 1;
            while (digit_count_ < target_size)
                digits_[digit_count_++] = 0;

            uint64_t sum = 0;
            for (unsigned i = 0; i < rhs.digit_count_; ++i) {
                sum += digits_[i];
                sum += rhs.digits_[i];
                digits_[i] = sum;
                sum >>= 32;
            }
            for (unsigned i = rhs.digit_count_; i < digit_count_ && sum != 0; ++i) {
                sum += digits_[i];
                digits_[i] = sum;
                sum >>= 32;
            }

            while (digit_count_ > 1 && digits_[digit_count_-1] == 0)
                --digit_count_;

            return *this;
        }

    private:
        uint32_t digits_[1536] = {};
        unsigned digit_count_ = 0;

        friend std::ostream& operator <<(std::ostream& output, integer& x)
        {
            std::string value;
            value.reserve(15360);
            do {
                uint64_t carry = 0;
                for (int i = x.digit_count_ - 1; i >= 0; --i) {
                    carry <<= 32;
                    carry += x.digits_[i];
                    x.digits_[i] = carry / 1000000000;
                    carry %= 1000000000;
                }
                while (x.digit_count_ > 1 && x.digits_[x.digit_count_-1] == 0)
                    --x.digit_count_;

                for (size_t i = 0; i < 9; ++i) {
                    value.push_back('0' + carry % 10);
                    carry /= 10;
                }
            } while (x.digit_count_ > 1 || x.digits_[0] != 0);

            while (value.length() > 1 && value.back() == '0')
                value.pop_back();

            for (auto it = value.rbegin(); it != value.rend(); ++it)
                output << *it;

            return output;
        }

    }; // class integer

} // namespace long_arithmetic

using long_arithmetic::integer;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    integer x[2] = { 4, 7 };
    for (unsigned i = 4, j = 0; i < n; ++i, j ^= 1)
        x[j] += x[j ^ 1];

    std::cout << x[n % 2 ^ 1] << '\n';

    return 0;
}
