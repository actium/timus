#include <iostream>
#include <string>

int main()
{
    std::string t;
    std::cin >> t;

    unsigned n;
    std::cin >> n;

    const unsigned x = (n & 0x000000FF) << 24 | (n & 0x0000FF00) << 8 | (n & 0x00FF0000) >> 8 | (n & 0xFF000000) >> 24;

    std::cout << x << '\n';

    return 0;
}
