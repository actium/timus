#include <iostream>
#include <string>

bool check(const std::string& s, size_t x, size_t p)
{
    for (size_t i = 0; i < 18; ++i) {
        if (s[x + i] != s[x + i + p])
            return false;
    }
    return true;
}

void solve(const std::string& a, const std::string& b)
{
    const size_t n = a.length() - 2, m = b.length() - 2;

    std::string sum(36, '0');
    for (size_t i = 0; i < 35; ++i) {
        sum[i] += a[n - i % n] - '0' + b[m - i % m] - '0';
        if (sum[i] > '9') {
            sum[i] -= 10;
            ++sum[i+1];
        }
    }

    std::pair<size_t, size_t> p = { ~0u, 0 };
    for (size_t i = 0; i <= 9; ++i) {
        for (size_t k = 1; k <= 9; ++k) {
            if (check(sum, i, k))
                p = std::min(p, std::make_pair(k, i));
        }
    }

    std::cout << '(';
    for (size_t i = p.first + p.second; i-- > p.second; std::cout << sum[i]);
    std::cout << ')';
    for (size_t i = p.second; i-- > 0; std::cout << sum[i]);
    std::cout << '\n';
}

int main()
{
    std::string a, b;
    std::cin >> a >> b;

    solve(a, b);

    return 0;
}
