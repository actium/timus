#include <iostream>

unsigned solve(unsigned n, unsigned m, unsigned k)
{
    using integer = unsigned long long;

    return std::min<integer>(m * integer(k + 1) / n, k);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m, k;
    std::cin >> n >> m >> k;

    std::cout << solve(n, m, k) << '\n';

    return 0;
}
