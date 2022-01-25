#include <iostream>

int main()
{
    unsigned c1, c2;
    std::cin >> c1 >> c2;

    if (c1 % 2 == 0 || c2 % 2 == 1)
        std::cout << "yes" << '\n';
    else
        std::cout << "no" << '\n';

    return 0;
}
