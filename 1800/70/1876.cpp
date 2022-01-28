#include <iostream>

int main()
{
    unsigned a, b;
    std::cin >> a >> b;

    std::cout << std::max(2 * a + 39, 2 * b + 40) << '\n';

    return 0;
}
