#include <iostream>
#include <string>

int main()
{
    unsigned n;
    std::cin >> n;

    unsigned k = 2 + n;
    while (n-- != 0) {
        std::string s;
        std::cin >> s;

        if (s.find('+') != std::string::npos)
            ++k;
    }

    if (k == 13)
        ++k;

    std::cout << k * 100 << '\n';

    return 0;
}
