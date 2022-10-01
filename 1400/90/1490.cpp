#include <iostream>

int main()
{
    using integer = unsigned long long;

    integer r;
    std::cin >> r;

    integer s = 0;
    for (integer x = 0, k = r; x < r; ++x) {
        while ((k - 1) * (k - 1) + x * x >= r * r)
            --k;

        s += k;
    }

    std::cout << 4 * s << '\n';

    return 0;
}
