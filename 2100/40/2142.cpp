#include <iostream>

bool check(unsigned& a, unsigned& b, unsigned& c)
{
    if (a + b < c)
        return false;

    if (a < c) {
        b -= c - a;
        a = 0;
    } else {
        a -= c;
    }

    return true;
}

bool solve(unsigned a, unsigned b, unsigned c, unsigned x, unsigned y, unsigned z)
{
    if (!check(a, c, x))
        return false;

    if (!check(b, c, y))
        return false;

    return a + b + c >= z;
}

int main()
{
    unsigned a, b, c;
    std::cin >> a >> b >> c;

    unsigned x, y, z;
    std::cin >> x >> y >> z;

    if (!solve(a, b, c, x, y, z))
        std::cout << "There are no miracles in life" << '\n';
    else
        std::cout << "It is a kind of magic" << '\n';

    return 0;
}
