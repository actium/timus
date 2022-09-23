#include <iomanip>
#include <iostream>
#include <string>

int main()
{
    constexpr double d = 1.4142135623730950488 / 2;

    constexpr double dx[10] = { 0, -d, 0, d, -1, 0, 1, -d, 0, d };
    constexpr double dy[10] = { 0, -d, -1, -d, 0, 0, 0, d, 1, d };

    std::string s;
    std::cin >> s;

    double x = 0, y = 0;
    for (const char c : s) {
        if (c == '0')
            break;

        x += dx[c - '0'];
        y += dy[c - '0'];
    }

    std::cout << std::fixed << std::setprecision(10) << x << ' ' << y << '\n';

    return 0;
}
