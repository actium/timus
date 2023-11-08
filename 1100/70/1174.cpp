#include <iostream>
#include <string>
#include <vector>

class Integer {
public:
    Integer(unsigned value)
    {
        const std::string v = std::to_string(value);
        value_.assign(v.rbegin(), v.rend());

        for (uint8_t& c : value_)
            c -= '0';
    }

    Integer& operator +=(const Integer& rhs)
    {
        const size_t m = rhs.value_.size(), n = std::max(value_.size(), m);

        value_.resize(n + 1);
        for (size_t i = 0; i < m; ++i) {
            value_[i] += rhs.value_[i];
            if (value_[i] > 9) {
                value_[i] -= 10;
                ++value_[i+1];
            }
        }
        for (size_t i = m; i < n && value_[i] > 9; ++i) {
            value_[i] -= 10;
            ++value_[i+1];
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
                const unsigned y = value_[i] * rhs.value_[j] + product[i+j];
                product[i+j+0] = y % 10;
                product[i+j+1] += y / 10;
            }
        }
        value_.swap(product);
        normalize();
        return *this;
    }

private:
    void normalize()
    {
        while (value_.size() > 1 && value_.back() == 0)
            value_.pop_back();
    }

private:
    std::vector<uint8_t> value_;

    friend std::ostream& operator <<(std::ostream& output, const Integer& v)
    {
        std::string value(v.value_.rbegin(), v.value_.rend());
        for (char& c : value)
            c += '0';

        return output << value;
    }

}; // class Integer

Integer operator +(const Integer& lhs, const Integer& rhs)
{
    return Integer(lhs) += rhs;
}

Integer operator *(const Integer& lhs, const Integer& rhs)
{
    return Integer(lhs) *= rhs;
}

std::pair<Integer, int> index(const std::vector<unsigned>& p, unsigned x)
{
    if (x == 1)
        return { 0, 0 };

    unsigned d = 1;
    for (auto it = p.begin(); *it != x; ++it)
        d += (*it < x);

    const std::pair<Integer, int> v = index(p, x - 1);
    if (v.second == 0)
        return { v.first * x + (x - d), (x - d) % 2 };

    return { v.first * x + (d - 1), (x + d - 1) % 2 };
}

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> p(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> p[i];

    std::cout << index(p, n).first + 1;

    return 0;
}
