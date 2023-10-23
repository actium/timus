#include <iostream>

struct Point {
    int x;
    int y;
};

int cross_product(const Point& a, const Point& b)
{
    return a.x * b.y - a.y * b.x;
}

int dot_product(const Point& a, const Point& b)
{
    return a.x * b.x + a.y * b.y;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned d;
    std::cin >> d;

    Point b[2];
    std::cin >> b[0].x >> b[0].y >> b[1].x >> b[1].y;

    const auto check = [=](const Point& p) {
        if (p.x * p.x + p.y * p.y > d * d)
            return false;

        if (cross_product(b[0], p) < 0 || cross_product(b[1], p) > 0)
            return false;

        return dot_product(b[0], p) >= 0 || dot_product(b[1], p) >= 0;
    };

    size_t n;
    std::cin >> n;

    for (size_t i = 0; i < n; ++i) {
        Point p;
        std::cin >> p.x >> p.y;

        std::cout << (check(p) ? "YES" : "NO") << '\n';
    }

    return 0;
}
