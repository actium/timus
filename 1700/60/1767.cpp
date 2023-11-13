#include <algorithm>
#include <iostream>

unsigned solve(const std::pair<int, int> (& p)[4])
{
    const std::pair<int, int> q[4] = {
        { std::min(p[0].first, p[1].first), std::min(p[0].second, p[1].second) },
        { std::max(p[0].first, p[1].first), std::max(p[0].second, p[1].second) },
        { std::min(p[2].first, p[3].first), std::min(p[2].second, p[3].second) },
        { std::max(p[2].first, p[3].first), std::max(p[2].second, p[3].second) },
    };

    const auto intersection = [](int s1, int t1, int s2, int t2) {
        return s1 < t1 ? std::min({s2 - t1, t2 - t1, s2 - s1}) : std::min({t2 - s1, s2 - s1, t2 - t1});
    };

    const int d1 = intersection(q[0].first, q[2].first, q[1].first, q[3].first);
    if (d1 < 0)
        return 0;

    const int d2 = intersection(q[0].second, q[2].second, q[1].second, q[3].second);
    if (d2 < 0)
        return 0;

    const long long dx1 = p[1].first - p[0].first, dy1 = p[1].second - p[0].second;
    const long long dx2 = p[3].first - p[2].first, dy2 = p[3].second - p[2].second;

    return (dx1 * dx2 ^ dy1 * dy2) < 0 ? std::max(d1, d2) : d1 + d2;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::pair<int, int> p[4];
    for (size_t i = 0; i < 4; ++i)
        std::cin >> p[i].first >> p[i].second;

    std::cout << solve(p) << '\n';

    return 0;
}
