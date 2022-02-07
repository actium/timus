#include <iostream>

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    std::cout << n * (n - 1) / 2 - k << '\n';

    return 0;
}
