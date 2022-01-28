#include <iostream>

int main()
{
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;

    while (a + b < c) {
        a += b;
        c -= d;
    }

    std::cout << std::max(a, c) << '\n';

    return 0;
}
