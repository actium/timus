#include <algorithm>
#include <iostream>
#include <map>
#include <string>

int main()
{
    unsigned n;
    std::cin >> n >> std::ws;

    std::map<std::string, unsigned> f;
    while (n-- != 0) {
        std::string s;
        std::getline(std::cin, s);

        ++f[s];
    }

    const auto x = std::max_element(f.cbegin(), f.cend(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    std::cout << x->first << '\n';

    return 0;
}
