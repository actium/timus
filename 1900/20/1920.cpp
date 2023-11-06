#include <iostream>

void segment4(unsigned n, unsigned l, unsigned x, unsigned y)
{
    while (x > 1)
        std::cout << x-- << ' ' << y << '\n';

    while (y > 1)
        std::cout << x << ' ' << y-- << '\n';
}

void segment3(unsigned n, unsigned l, unsigned x, unsigned y)
{
    for (int d = -1; l != 0; --l) {
        if (d == -1 && x + y == l + 2)
            return segment4(n, l, x, y);

        std::cout << x << ' ' << y << '\n';

        if (d == 1 && x == 1) {
            ++x;
            continue;
        }
        if (d == -1 && x == 2) {
            --x;
            continue;
        }

        d = -d;
        --y;
    }
}

void segment2(unsigned n, unsigned l, unsigned x, unsigned y)
{
    for (int d = 1; l != 0; --l) {
        if (x + y == l + 2)
            return segment4(n, l, x, y);

        std::cout << x << ' ' << y << '\n';

        if (d == 1 && y < n) {
            ++y;
            continue;
        }
        if (d == -1 && y > 2) {
            --y;
            continue;
        }

        d = -d;

        if (--x == 2 && d == -1 && n % 2 == 1)
            return segment3(n, l - 1, x, y);
    }
}

void segment1(unsigned n, unsigned l, unsigned x, unsigned y)
{
    while (x <= n) {
        std::cout << x << ' ' << y << '\n';

        if (--l == x)
            return segment4(n, l, x, y + 1);

        ++x;
    }

    segment2(n, l, x - 1, y + 1);
}

void solve(unsigned n, unsigned l)
{
    if (l % 2 == 1 || n * n < l) {
        std::cout << "Unsuitable device" << '\n';
    } else {
        std::cout << "Overwhelming power of magic" << '\n';
        segment1(n, l, 1, 1);
    }
}

int main()
{
    unsigned n, l;
    std::cin >> n >> l;

    solve(n, l);

    return 0;
}
