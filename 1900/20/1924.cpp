#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    std::cout << ((n - 1) % 4 < 2 ? "grimy" : "black") << '\n';

    return 0;
}
