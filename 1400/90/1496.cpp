#include <iostream>
#include <unordered_map>

int main()
{
    unsigned n;
    std::cin >> n;

    std::unordered_map<std::string, unsigned> f;
    while (n-- > 0) {
        std::string s;
        std::cin >> s;

        if (f[s]++ == 1)
            std::cout << s << '\n';
    }

    return 0;
}
