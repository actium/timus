#include <iostream>

void solve(unsigned n)
{
    unsigned x = 1;
    switch (n % 6) {
        case 2:
            for (unsigned y = 2; y <= n; y += 2)
                std::cout << x++ << ' ' << y << '\n';
            std::cout << x++ << ' ' << '3' << '\n';
            std::cout << x++ << ' ' << '1' << '\n';
            for (unsigned y = 7; y <= n; y += 2)
                std::cout << x++ << ' ' << y << '\n';
            std::cout << x++ << ' ' << '5' << '\n';
            break;

        case 3:
            for (unsigned y = 4; y <= n; y += 2)
                std::cout << x++ << ' ' << y << '\n';
            std::cout << x++ << ' ' << '2' << '\n';
            for (unsigned y = 5; y <= n; y += 2)
                std::cout << x++ << ' ' << y << '\n';
            std::cout << x++ << ' ' << '1' << '\n';
            std::cout << x++ << ' ' << '3' << '\n';
            break;

        default:
            for (unsigned y = 2; y <= n; y += 2)
                std::cout << x++ << ' ' << y << '\n';
            for (unsigned y = 1; y <= n; y += 2)
                std::cout << x++ << ' ' << y << '\n';
            break;
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    solve(n);

    return 0;
}
