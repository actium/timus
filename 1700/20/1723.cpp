#include <iostream>
#include <string>

int main()
{
    std::string s;
    std::cin >> s;

    size_t x = 0;

    unsigned f[26] = {};
    for (const char c : s) {
        const size_t p = c - 'a';
        if (++f[p] > f[x])
            x = p;
    }

    std::cout << char('a' + x) << '\n';

    return 0;
}
