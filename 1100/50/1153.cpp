#include <iostream>
#include <string>
#include <vector>

class Integer {
public:
    Integer(const std::string& value)
        : value_(value.length())
    {
        const size_t n = value_.size();

        for (size_t i = 0; i < n; ++i)
            value_[i] = value[n-1-i] - '0';

        normalize();
    }

    explicit operator std::string() const
    {
        const size_t n = value_.size();

        std::string value(n, '0');
        for (size_t i = 0; i < n; ++i)
            value[i] += value_[n - 1 - i];

        return value;
    }

    Integer& operator ++()
    {
        value_.push_back(0);
        for (size_t i = 0; ++value_[i] == 10; ++i)
            value_[i] = 0;

        normalize();
        return *this;
    }

    Integer& operator +=(const Integer& rhs)
    {
        const size_t m = rhs.value_.size(), n = std::max(value_.size(), m);

        value_.resize(n + 1);
        for (size_t i = 0; i < m; ++i) {
            value_[i] += rhs.value_[i];
            if (value_[i] >= 10) {
                ++value_[i + 1];
                value_[i] -= 10;
            }
        }

        normalize();
        return *this;
    }

    Integer& operator *=(const Integer& rhs)
    {
        const size_t n = value_.size(), m = rhs.value_.size();

        std::vector<uint8_t> product(n + m);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                const unsigned c = product[i + j];
                const unsigned y = value_[i] * rhs.value_[j] + c;

                product[i + j + 0] = y % 10;
                product[i + j + 1] += y / 10;
            }
        }

        value_.swap(product);
        normalize();
        return *this;
    }

    Integer& operator >>=(unsigned k)
    {
        value_.erase(value_.begin(), value_.begin() + k);
        return *this;
    }

    int compare(const Integer& rhs) const
    {
        const size_t n = value_.size();
        if (n != rhs.value_.size())
            return n - rhs.value_.size();

        for (size_t i = n - 1; ~i; --i) {
            if (value_[i] != rhs.value_[i])
                return value_[i] - rhs.value_[i];
        }
        return 0;
    }

private:
    void normalize()
    {
        while (value_.back() == 0 && value_.size() > 1)
            value_.pop_back();
    }

private:
    std::vector<uint8_t> value_;

}; // class Integer

Integer increment(Integer v)
{
    return ++v;
}

Integer operator +(Integer lhs, const Integer& rhs)
{
    return lhs += rhs;
}

Integer operator *(Integer lhs, const Integer& rhs)
{
    return lhs *= rhs;
}

Integer operator >>(Integer v, unsigned k)
{
    return v >>= k;
}

bool operator <(const Integer& lhs, const Integer& rhs)
{
    return lhs.compare(rhs) < 0;
}

bool operator >(const Integer& lhs, const Integer& rhs)
{
    return rhs < lhs;
}

std::string solve(const std::string& n)
{
    const Integer x = Integer("2") * n, f = Integer("5");

    const auto half = [&f](Integer x) {
        x *= f;
        return x >> 1;
    };

    Integer lb = Integer("0"), ub = "1" + std::string(n.length() / 2 + 1, '0');
    while (increment(lb) < ub) {
        Integer mid = half(lb + ub);
        (mid * increment(mid) > x ? ub : lb) = std::move(mid);
    }
    return std::string(lb);
}

int main()
{
    std::string s;
    std::cin >> s;

    std::cout << solve(s) << '\n';

    return 0;
}
