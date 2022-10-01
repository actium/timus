#include <iostream>

int main()
{
    unsigned k;
    std::cin >> k;

    unsigned x = 3;
    while (k % x != 0)
        ++x;

    std::cout << x - 1 << '\n';

    return 0;
}
