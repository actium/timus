#include <array>
#include <iostream>

struct Point {
    unsigned x;
    unsigned y;
};

bool check(const std::array<Point, 4>& p)
{
    unsigned d[4] = {};
    for (size_t i = 1; i < 4; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (p[i].x == p[j].x && p[i].y == p[j].y)
                return false;

            if (p[i].x == p[j].x || p[i].y == p[j].y) {
                ++d[i];
                ++d[j];
            }
        }
    }
    return d[0] == 1 && d[1] == 1 && d[2] == 1 && d[3] == 1;
}

bool search(std::array<Point, 4>& p, unsigned k)
{
    if (k == 0)
        return check(p);

    for (size_t i = 0; i < 4; ++i) {
        std::array<Point, 4> q = p;
        for (unsigned u = 0; u < 20 * 20; ++u) {
            q[i].x = u / 20 + 1;
            q[i].y = u % 20 + 1;

            if (search(q, k - 1)) {
                p = q;
                return true;
            }
        }
    }
    return false;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::array<Point, 4> p;
    for (size_t i = 0; i < 4; ++i)
        std::cin >> p[i].x >> p[i].y;

    for (unsigned k = 0; !search(p, k); ++k);

    for (size_t i = 0; i < 4; ++i)
        std::cout << p[i].x << ' ' << p[i].y << '\n';

    return 0;
}
