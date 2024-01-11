#include <iostream>

int main()
{
    unsigned l, h, u;
    std::cin >> l >> h >> u;

    unsigned v, x, a;
    std::cin >> v >> x >> a;

    std::cout << (1ull*v*v*x + 2ull*l*a*x < 2ull*v*(u-h)*a ? "Safe" : "Crash") << '\n';

    return 0;
}
