#include <iostream>
#include <vector>

using integer = unsigned long long;

unsigned solve(const std::vector<unsigned>& r, const std::vector<unsigned>& c, size_t a, size_t b)
{
    integer rsum = 0;
    for (const unsigned v : r)
        rsum += v;

    integer csum = 0;
    for (const unsigned v : c)
        csum += v;

    if (rsum != csum)
        return 0;

    const unsigned ub = std::min(r[a], c[b]);

    const unsigned c1 = (c[b] > rsum - r[a] ? c[b] - (rsum - r[a]) : 0);
    const unsigned c2 = (r[a] > csum - c[b] ? r[a] - (csum - c[b]) : 0);

    const unsigned lb = std::max(c1, c2);

    return ub - lb + 1;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    unsigned a, b;
    std::cin >> a >> b;

    std::vector<unsigned> r(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> r[i];

    std::vector<unsigned> c(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> c[i];

    std::cout << solve(r, c, a-1, b-1) << '\n';;

    return 0;
}
