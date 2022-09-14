#include <iostream>

int main()
{
    unsigned l, k, h;
    std::cin >> l >> k >> h;

    std::cout << l / k * h << ' ' << (l + k - 1) / k * h << '\n';

    return 0;
}
