#include <iostream>
#include <string>

int main()
{
    size_t n, m, p;
    std::cin >> n >> m >> p;

    unsigned f[26] = {};
    for (size_t i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;

        for (const char c : s)
            ++f[c-'A'];
    }

    for (size_t i = 0; i < p; ++i) {
        std::string s;
        std::cin >> s;

        for (const char c : s)
            --f[c-'A'];
    }

    for (size_t i = 0; i < 26; ++i)
        std::cout << std::string(f[i], 'A' + i);

    return 0;
}
