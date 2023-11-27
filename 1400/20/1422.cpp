#include <iostream>
#include <map>
#include <numeric>
#include <vector>

struct Point {
    int x;
    int y;
    int z;
};

struct Slope {
    int x;
    int y;
    int z;

    Slope(int dx, int dy, int dz)
        : x(dx)
        , y(dy)
        , z(dz)
    {
        if (x <= 0 && y <= 0 && z <= 0) {
            x = -x;
            y = -y;
            z = -z;
        }

        const int g = std::gcd(std::gcd(dx, dy), dz);
        x /= g;
        y /= g;
        z /= g;
    }
};

bool operator <(const Slope& lhs, const Slope& rhs)
{
    return std::make_tuple(lhs.x, lhs.y, lhs.z) < std::make_tuple(rhs.x, rhs.y, rhs.z);
}

unsigned solve(const std::vector<Point>& p)
{
    const size_t n = p.size();

    unsigned k = 0;
    for (size_t i = 0; i < n; ++i) {
        unsigned c = 0;

        std::map<Slope, unsigned> f;
        for (size_t j = i + 1; j < n; ++j) {
            const int dx = p[i].x - p[j].x, dy = p[i].y - p[j].y, dz = p[i].z - p[j].z;
            c = std::max(c, ++f[Slope(dx, dy, dz)]);
        }

        k = std::max(k, c + 1);
    }
    return k;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Point> p(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> p[i].x >> p[i].y >> p[i].z;

    std::cout << solve(p) << '\n';

    return 0;
}
