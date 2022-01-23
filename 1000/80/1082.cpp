#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    std::cout << 0;
    for (unsigned i = 1; i < n; std::cout << ' ' << i++);
    std::cout << '\n';

    return 0;
}
