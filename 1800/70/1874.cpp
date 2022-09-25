#include <iostream>

int main()
{
    unsigned a, b;
    std::cin >> a >> b;

    const double s = (a * a + b * b) / 4.0 + a * b / 1.4142135623730950488;

    std::cout << std::fixed << s << '\n';

    return 0;
}
