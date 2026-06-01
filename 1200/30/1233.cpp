#include <iostream>
#include <string>

using integer = unsigned long long;

constexpr auto oo = ~integer(0);

integer count(integer q, integer n)
{
    const auto s = std::to_string(q);
    const auto m = s.size();

    integer k = m - 1, x = 0;
    for (size_t i = 0; i < m; ++i) {
        const unsigned b = s[i] - '0';

        for (unsigned d = (i == 0); d < b; ++d) {
            for (auto lb = x * 10 + d, ub = lb + 1; lb <= n; lb *= 10, ub *= 10)
                k += std::min(n + 1, ub) - lb;
        }

        x = x * 10 + b;
    }
    return k;
}

integer solve(unsigned k, unsigned m)
{
    integer lb = k-1, ub = oo;
    while (ub - lb > 1) {
        const integer mid = lb + (ub - lb) / 2;
        (count(k, mid) < m-1 ? lb : ub) = mid;
    }
    return count(k, ub) == m-1 ? ub : 0;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned k, m;
    std::cin >> k >> m;

    std::cout << solve(k, m) << '\n';

    return 0;
}
