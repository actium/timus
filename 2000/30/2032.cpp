#include <iostream>

#include <cmath>

using integer = long long;

void print_point(integer x, integer y)
{
    std::cout << x << ' ' << y << '\n';
}

void no_solution()
{
    std::cout << -1 << '\n';
}

void solve(integer a, integer b, integer c)
{
    if ((a + b + c) % 2 != 0)
        return no_solution();

    if (a > b)
        std::swap(a, b);
    if (b > c)
        std::swap(b, c);

    const __int128_t t = c * c, k = (t + a * a - b * b) / 2, D = t * a * a - k * k, m = sqrt(D);
    if (m * m != D)
        return no_solution();

    const auto check = [&](integer dx, integer dy, integer& x, integer& y) {
        if ((k * dx - m * dy) % t == 0 && (k * dy + m * dx) % t == 0) {
            x = (k * dx - m * dy) / t;
            y = (k * dy + m * dx) / t;
            return true;
        }
        return false;
    };

    for (integer dx = c, dy = 0; dx != 0; --dx) {
        while (dx * dx + dy * dy < t)
            ++dy;

        if (integer x, y; dx * dx + dy * dy == t && check(dx, dy, x, y)) {
            print_point(0, 0);
            print_point(dx, dy);
            print_point(x, y);
            return;
        }
    }

    no_solution();
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    integer a, b, c;
    std::cin >> a >> b >> c;

    solve(a, b, c);

    return 0;
}
