#include <iostream>

using integer = unsigned long long;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    const integer q = n * (n - 3ull) / 2;

    switch (n) {
        case 4:
            std::cout << '0';
            break;
        case 5:
            std::cout << '0';
            break;
        case 6:
            std::cout << '6';
            break;
        default:
            std::cout << q;
            break;
    }

    std::cout << ' ';

    if ((n & 1) == 0)
        std::cout << q;
    else
        std::cout << '0';

    return 0;
}
