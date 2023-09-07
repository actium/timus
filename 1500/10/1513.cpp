#include <iostream>
#include <string>
#include <vector>

class Integer {
public:
    Integer() = default;

    explicit Integer(const std::string& value)
        : value_(value)
    {}

    void make_double()
    {
        const size_t n = value_.length();

        value_.push_back('0');

        unsigned c = 0;
        for (size_t i = 0; i < n; ++i) {
            value_[i] = '0' + (value_[i] - '0') * 2 + c;
            if (value_[i] > '9') {
                value_[i] -= 10;
                c = 1;
            } else {
                c = 0;
            }
        }
        value_[n] += c;

        while (value_.back() == '0')
            value_.pop_back();
    }

    void subtract(const Integer& rhs)
    {
        const size_t n = value_.length(), m = rhs.value_.length();

        for (size_t i = 0; i < n; ++i) {
            const char d = (i < m ? rhs.value_[i] : '0');
            if (value_[i] < d) {
                value_[i] += 10;
                --value_[i+1];
            }
            value_[i] -= d - '0';
        }

        while (value_.back() == '0')
            value_.pop_back();
    }

    void print(std::ostream& output) const
    {
        for (auto it = value_.rbegin(); it != value_.rend(); ++it)
            output << *it;
    }

private:
    std::string value_ = "0";

}; // class Integer

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    std::vector<Integer> dp(2 + n);
    dp[0] = Integer("1");
    dp[1] = Integer("1");
    for (unsigned i = 2; i <= n + 1; ++i) {
        dp[i] = dp[i-1];
        dp[i].make_double();
        if (i > k + 1)
            dp[i].subtract(dp[i-k-2]);
    }

    dp[n+1].print(std::cout);

    return 0;
}
