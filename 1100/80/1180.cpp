#include <iostream>
#include <string>

int main()
{
    std::string n;
    std::cin >> n;

    unsigned v = 0, b = 1;
    for (const char c : n) {
        v += (c - '0') * b % 3;
        b = b * 10 % 3;
    }

    switch (v % 3) {
        case 0:
            std::cout << 2 << '\n';
            break;
        case 1:
            std::cout << 1 << '\n';
            std::cout << 1 << '\n';
            break;
        case 2:
            std::cout << 1 << '\n';
            std::cout << 2 << '\n';
            break;
    }

    return 0;
}
