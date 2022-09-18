#include <iostream>
#include <vector>

bool check(const std::vector<std::pair<int, int>>& p, size_t i)
{
    const long long dx = p[i].first - p[0].first, dy = p[i].second - p[0].second;

    unsigned k = 0;
    for (const std::pair<int, int>& x : p) {
        const long long cp = dx * (x.second - p[0].second) - dy * (x.first - p[0].first);
        if (cp < 0)
            ++k;
    }
    return 2 * k == p.size() - 2;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<std::pair<int, int>> p(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> p[i].first >> p[i].second;

    size_t i = 1;
    while (i < n && !check(p, i))
        ++i;

    std::cout << 1 << ' ' << 1+i << '\n';

    return 0;
}
