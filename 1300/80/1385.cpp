#include <iostream>
#include <string>

int main()
{
    unsigned n;
    std::cin >> n;

    switch (n) {
        case 1:
            std::cout << "14" << '\n';
            break;

        case 2:
            std::cout << "155" << '\n';
            break;

        default:
            std::cout << "1575" + std::string(n - 3, '0') << '\n';
            break;
    }

    return 0;
}
