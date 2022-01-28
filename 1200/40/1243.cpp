#include <iostream>
#include <string>

int main()
{
    std::string n;
    std::cin >> n;

    unsigned x = 1, r = 0;
    for (auto it = n.crbegin(); it != n.crend(); ++it) {
        r += (*it - '0') * x;
        x = x * 10 % 7;
    }

    std::cout << r % 7 << '\n';

    return 0;
}
