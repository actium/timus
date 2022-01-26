#include <iostream>

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    std::cout << std::max(2u, (2 * n + k - 1) / k) << '\n';

    return 0;
}
