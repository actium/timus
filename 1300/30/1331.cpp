#include <iostream>
#include <vector>

#include <cmath>

const double pi = acos(-1), rx = pi / 180;

struct Point {
    double x;
    double y;
    double z;
};

std::istream& operator >>(std::istream& input_stream, Point& point)
{
    double lat, lon;
    input_stream >> lat >> lon;

    lat *= rx;
    lon *= rx;

    const auto q = cos(lat);
    point.x = q * cos(lon);
    point.y = q * sin(lon);
    point.z = sin(lat);

    return input_stream;
}

double dot_product(const Point& s, const Point& t)
{
    return s.x * t.x + s.y * t.y + s.z * t.z;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cout.precision(2);

    size_t n, m;
    std::cin >> n >> m;

    double r;
    std::cin >> r;

    std::vector<Point> ps(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> ps[i];

    for (size_t i = 0; i < n; ++i) {
        Point s;
        std::cin >> s;

        double dp = dot_product(s, ps[0]);
        for (size_t j = 1; j < m; ++j)
            dp = std::max(dp, dot_product(s, ps[j]));

        dp = std::max(-1.0, std::min(dp, 1.0));

        std::cout << std::fixed << acos(dp) * r << '\n';
    }

    return 0;
}
