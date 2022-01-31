#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    std::cout << n * (n + 1ull) * (n + 2) / 2 << '\n';

    return 0;
}
