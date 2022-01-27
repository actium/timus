#include <iostream>
#include <string>

int main()
{
    std::string s;
    std::getline(std::cin, s);

    unsigned x = 0;
    for (const char c : s) {
        switch (c) {
            case ' ': x += 1; break;
            case '.': x += 1; break;
            case ',': x += 2; break;
            case '!': x += 3; break;
            default: x += (c - 'a') % 3 + 1;
        }
    }

    std::cout << x << '\n';

    return 0;
}
