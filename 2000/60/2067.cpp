#include <algorithm>
#include <iostream>
#include <vector>

void solve(const std::vector<std::pair<int, int>>& p)
{
    const auto r = std::minmax_element(p.begin(), p.end());

    const auto check = [&](const std::pair<int, int>& q) {
        const long long dx1 = q.first - r.first->first, dy1 = q.second - r.first->second;
        const long long dx2 = r.second->first - q.first, dy2 = r.second->second - q.second;
        return dx1 * dy2 == dx2 * dy1;
    };

    for (const std::pair<int, int>& q : p) {
        if (!check(q)) {
            std::cout << 0 << '\n';
            return;
        }
    }

    std::cout << 1 << '\n';
    std::cout << 1 + r.first - p.begin() << ' ' << 1 + r.second - p.begin() << '\n';
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

    solve(p);

    return 0;
}
