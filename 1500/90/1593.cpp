#include <algorithm>
#include <iostream>
#include <vector>

using integer = unsigned long long;

using factor_t = std::pair<integer, unsigned>;

std::vector<factor_t> factorize(integer n)
{
    std::vector<factor_t> fs;
    if (n % 2 == 0) {
        fs.emplace_back(2, __builtin_ctzll(n));
        n >>= fs.back().second;
    }
    for (integer i = 3; i * i <= n; i += 2) {
        if (n % i != 0)
            continue;

        fs.emplace_back(i, 0);
        while (n % i == 0) {
            ++fs.back().second;
            n /= i;
        }
    }
    if (n != 1)
        fs.emplace_back(n, 1);

    return fs;
}

unsigned solve(integer n)
{
    if (n == 0)
        return 0;

    const std::vector<factor_t> fs = factorize(n);

    if (std::none_of(fs.begin(), fs.end(), [](const factor_t& f) { return f.second % 2 == 1; }))
        return 1;

    if (std::all_of(fs.begin(), fs.end(), [](const factor_t& f) { return f.first % 4 != 3 || f.second % 2 == 0; }))
        return 2;

    const unsigned m = __builtin_clzll(1) - __builtin_clzll(~n & n - 1) + 1;

    return m % 2 == 0 && (n >> m) % 8 == 7 ? 4 : 3;
}

int main()
{
    integer n;
    std::cin >> n;

    std::cout << solve(n) << '\n';

    return 0;
}
