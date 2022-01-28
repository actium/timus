#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    switch (n) {
        case 1:
            std::cout << "1 2 3" << '\n';
            break;
        case 2:
            std::cout << "3 4 5" << '\n';
            break;
        default:
            std::cout << "-1" << '\n';
    }

    return 0;
}
