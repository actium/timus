#include <iostream>

int main()
{
    constexpr unsigned x[] = { 0, 0, 10, 0, 670, 0, 55252, 0, 4816030 };

    unsigned n;
    std::cin >> n;

    std::cout << x[n] << '\n';

    return 0;
}
