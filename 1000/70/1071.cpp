#include <iostream>

void solve(unsigned x, unsigned y)
{
    for (unsigned r = 2; r <= x; ++r) {
        unsigned u = x, v = y;
        while (u > v) {
            if (u % r == v % r)
                v /= r;

            u /= r;
        }

        if (u == v) {
            std::cout << r << '\n';
            return;
        }
    }

    std::cout << "No solution" << '\n';
}

int main()
{
    unsigned x, y;
    std::cin >> x >> y;

    solve(x, y);

    return 0;
}
