#include <iostream>

int main()
{
    int x, y;
    std::cin >> x >> y;

    if (x > 0 && y > 0 && (x + y) % 2 == 1)
        std::swap(x, y);

    std::cout << x << ' ' << y << '\n';

    return 0;
}
