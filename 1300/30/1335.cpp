#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    std::cout << n * (n + 2) << ' ' << n * (n + 1) << ' ' << n * (n + 0) << '\n';

    return 0;
}
