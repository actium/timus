#include <iostream>

#include <cmath>

const auto pi = std::acos(-1.0), epsilon = 1e-15;

int main()
{
    long double lat, lon;
    scanf("%Lf %Lf", &lat, &lon);

    long double d;
    scanf("%Lf", &d);

    lat *= pi / 180;
    lon *= pi / 180;

    const auto delta = d / 6400;

    const auto x1 = lat + delta;
    const auto lat1 = std::asin(std::sin(x1));
    const auto lon1 = lon + (std::cos(x1) < 0 ? pi : 0);

    const auto x2 = std::cos(lat1);
    const auto lat2 = lat1;
    const auto lon2 = lon1 + (std::abs(x2) > epsilon ? delta / x2 : 0);

    const auto x3 = lat2 - delta;
    const auto lat3 = std::asin(std::sin(x3));
    const auto lon3 = lon2 + (std::cos(x3) < 0 ? pi : 0);

    const auto x4 = std::cos(lat3);
    const auto lat4 = lat3;
    const auto lon4 = lon3 - (std::abs(x4) > epsilon ? delta / x4 : 0);

    lat = lat4 * 180 / pi;
    lon = std::fmod(lon4 * 180 / pi, 360);

    if (lon > 180)   lon -= 360;
    if (lon <= -180) lon += 360;

    printf("%.3Lf\n", lat);
    printf("%.3Lf\n", lon);

    return 0;
}
