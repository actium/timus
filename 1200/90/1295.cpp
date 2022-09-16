#include <iostream>

int main()
{
    constexpr unsigned t[] = { 0, 1, 1, 2, 0, 2, 1, 2, 0, 1, 1, 2, 0, 1, 1, 2, 0, 1, 1, 2 };

    unsigned n;
    std::cin >> n;

    std::cout << t[n % 20] << '\n';

    return 0;
}
