#include <iostream>
#include <string>

constexpr char t[] = { 0, 1, 2, 3, 2, 1, 2, 3, 4, 2 };

int main()
{
    std::string n;
    std::cin >> n;

    unsigned k = 0;
    for (const char c : n)
        k += t[c - '0'];

    std::cout << k << '\n';

    return 0;
}
