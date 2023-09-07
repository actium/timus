#include <iostream>

int main()
{
    unsigned a, b, d;
    std::cin >> a >> b >> d;

    std::pair<unsigned, unsigned> p[2];
    std::cin >> p[0].first >> p[0].second;
    std::cin >> p[1].first >> p[1].second;

    unsigned h;
    std::cin >> h;

    if (a < b)
        std::swap(a, b);

    unsigned r[2];
    if (h > d) {
        r[0] = p[0].second * h - (h - d) * (p[0].second - p[0].first);
        r[1] = p[1].second * h - (h - d) * (p[1].second - p[1].first);
    } else {
        r[0] = p[0].second * h;
        r[1] = p[1].second * h;
    }

    const auto solve = [&] {
        if (2 * r[0] > b * h || 2 * r[1] > b * h)
            return false;

        const long long dx = a * h - r[0] - r[1], dy = b * h - r[0] - r[1], rs = p[0].second + p[1].second;
        if (dx * dx + dy * dy < rs * rs * h  * h)
            return false;

        return true;
    };

    std::cout << (solve() ? "YES" : "NO") << '\n';

    return 0;
}
