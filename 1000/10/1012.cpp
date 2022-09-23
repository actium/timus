#include <iostream>
#include <string>
#include <utility>

std::string add(std::string lhs, std::string rhs)
{
    const size_t n = std::max(lhs.length(), rhs.length());

    lhs.resize(n, '0');
    rhs.resize(n, '0');

    std::string sum(n + 1, '0');
    for (size_t i = 0; i < n; ++i) {
        const unsigned d = (lhs[i] - '0') + (rhs[i] - '0') + (sum[i] - '0');
        sum[i] = '0' + d % 10;
        sum[i+1] += d / 10;
    }
    if (sum.back() == '0')
        sum.pop_back();

    return sum;
}

std::string multiply(std::string lhs, std::string rhs)
{
    const size_t n = lhs.length(), m = rhs.length();

    std::string product(n + m, '0');
    for (size_t i = 0; i < n; ++i) {
        const unsigned d1 = lhs[i] - '0';

        for (size_t j = 0; j < m; ++j) {
            const unsigned d2 = rhs[j] - '0';

            const unsigned c = product[i+j] - '0';
            const unsigned y = d1 * d2 + c;

            product[i+j] = '0' + y % 10;
            product[i+j+1] += y / 10;
        }
    }
    while (product.back() == '0')
        product.pop_back();

    return product;
}

std::string reverse(const std::string& s)
{
    return std::string(s.crbegin(), s.crend());
}

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    const std::string q = std::to_string(k - 1);

    std::string dp[4] = { "1", q };
    for (unsigned i = 2; i <= n; ++i)
        dp[i%4] = multiply(add(dp[(i-2)%4], dp[(i-1)%4]), q);

    std::cout << reverse(dp[n%4]) << '\n';

    return 0;
}
