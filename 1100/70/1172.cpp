#include <iostream>
#include <string>
#include <vector>

class Integer {
public:
    static Integer one()
    {
        return Integer("1");
    }

    Integer() = default;

    Integer operator +(const Integer& rhs) const
    {
        const size_t m = rhs.data_.length(), n = std::max(data_.length(), m);

        Integer value(data_);
        value.data_.resize(n + 1, '0');
        for (size_t i = 0; i < m; ++i) {
            value.data_[i] += rhs.data_[i] - '0';
            if (value.data_[i] > '9') {
                ++value.data_[i+1];
                value.data_[i] -= 10;
            }
        }

        while (value.data_.length() > 1 && value.data_.back() == '0')
            value.data_.pop_back();

        return value;
    }

    Integer operator *(unsigned rhs) const
    {
        const size_t n = data_.length();

        std::vector<unsigned> product(n + 5);
        for (size_t i = 0; i < n; ++i) {
            product[i] += (data_[i] - '0') * rhs;
            product[i+1] += product[i] / 10;
            product[i] %= 10;
        }
        for (size_t i = n; i < n + 5; ++i) {
            product[i+1] += product[i] / 10;
            product[i] %= 10;
        }

        Integer value;
        value.data_.assign(n + 5, '0');
        for (size_t i = 0; i < n + 5; ++i)
            value.data_[i] += product[i];

        while (value.data_.length() > 1 && value.data_.back() == '0')
            value.data_.pop_back();

        return value;
    }

private:
    explicit Integer(const std::string& data)
        : data_(data)
    {}

private:
    std::string data_ = "0";

    friend std::ostream& operator <<(std::ostream& output, const Integer& v)
    {
        return output << std::string(v.data_.rbegin(), v.data_.rend());
    }

}; // class Integer

Integer dp[3][31][31][31];

Integer solve(unsigned n)
{
    dp[0][1][0][0] = Integer::one();

    for (unsigned t = 1; t < 3 * n; ++t) {
        for (unsigned k1 = 1; k1 <= n; ++k1) {
            for (unsigned k2 = 0; k2 <= n && k1 + k2 <= t; ++k2) {
                const unsigned k3 = t - (k1 + k2);
                if (k3 > n)
                    continue;

                if (k1 < n)
                    dp[0][k1+1][k2][k3] = (dp[1][k1][k2][k3] + dp[2][k1][k2][k3]) * (n - k1);

                if (k2 < n)
                    dp[1][k1][k2+1][k3] = (dp[0][k1][k2][k3] + dp[2][k1][k2][k3]) * (n - k2);

                if (k3 < n)
                    dp[2][k1][k2][k3+1] = (dp[0][k1][k2][k3] + dp[1][k1][k2][k3]) * (n - k3);
            }
        }
    }

    return dp[1][n][n][n];
}

int main()
{
    unsigned n;
    std::cin >> n;

    std::cout << solve(n) << '\n';

    return 0;
}
