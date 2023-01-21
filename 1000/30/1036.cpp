#include <iostream>
#include <string>
#include <vector>

class LongInteger {
public:
    LongInteger()
        : data_(1)
    {}

    explicit LongInteger(const std::string& value)
    {
        data_.reserve(value.length() + 1);
        for (auto it = value.rbegin(); it != value.rend(); ++it)
            data_.push_back(*it - '0');

        normalize();
    }

    explicit operator std::string() const
    {
        std::string value;
        value.reserve(data_.size());
        for (auto it = data_.rbegin(); it != data_.rend(); ++it)
            value.push_back('0' + *it);

        return value;
    }

    LongInteger& operator ++()
    {
        data_.push_back(0);
        for (size_t i = 0; ++data_[i] == 10; ++i)
            data_[i] = 0;

        normalize();
        return *this;
    }

    LongInteger& operator --()
    {
        for (size_t i = 0; data_[i]-- == 0; ++i)
            data_[i] = 9;

        normalize();
        return *this;
    }

    LongInteger& operator +=(const LongInteger& rhs)
    {
        const size_t n = data_.size(), m = rhs.data_.size();

        data_.resize(std::max(n, m) + 1);
        for (size_t i = 0; i < m; ++i) {
            data_[i] += rhs.data_[i];
            if (data_[i] > 9) {
                data_[i] -= 10;
                ++data_[i + 1];
            }
        }
        for (size_t i = m; data_[i] > 9; ++i) {
            data_[i] -= 10;
            ++data_[i + 1];
        }

        normalize();
        return *this;
    }

    LongInteger& operator *=(const LongInteger& rhs)
    {
        const size_t n = data_.size(), m = rhs.data_.size();

        std::vector<uint8_t> product(n + m);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                const unsigned c = product[i + j];
                const unsigned v = data_[i] * rhs.data_[j] + c;

                product[i + j] = v % 10;
                product[i + j + 1] += v / 10;
            }
        }

        std::swap(data_, product);
        normalize();
        return *this;
    }

private:
    void normalize()
    {
        while (data_.back() == 0 && data_.size() > 1)
            data_.pop_back();
    }

private:
    std::vector<uint8_t> data_;

}; // class LongInteger

std::ostream& operator <<(std::ostream& output, const LongInteger& value)
{
    return output << static_cast<std::string>(value);
}

LongInteger solve(unsigned n, unsigned s)
{
    if (s > 900 || s % 2 != 0)
        return LongInteger();

    LongInteger c[n][s + 10];
    for (unsigned d = 0; d <= 9; ++d)
        ++c[0][d];

    for (unsigned i = 1; i < n; ++i) {
        for (unsigned d = 0; d <= 9; ++d) {
            for (unsigned j = d; j <= s; ++j)
                c[i][j] += c[i-1][j-d];
        }
    }

    LongInteger k = c[n-1][s/2];
    k *= k;
    return k;
}

int main()
{
    unsigned n, s;
    std::cin >> n >> s;

    std::cout << solve(n, s) << '\n';

    return 0;
}
