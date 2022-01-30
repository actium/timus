#include <iostream>

int main()
{
    unsigned long long n, m;
    std::cin >> n >> m;

    if (m < n)
        std::cout << (m - 1) * 2 + 1 << '\n';
    else
        std::cout << (n - 1) * 2 << '\n';

    return 0;
}
