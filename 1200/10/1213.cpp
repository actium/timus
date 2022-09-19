#include <iostream>
#include <set>
#include <string>

int main()
{
    std::string s;
    std::cin >> s;

    std::set<std::string> c;
    for (std::string x; std::cin >> x && x != "#"; ) {
        const size_t p = x.find('-');
        c.insert(x.substr(0, p));
        c.insert(x.substr(p+1));
    }

    std::cout << (c.empty() ? 0 : c.size() - 1) << '\n';

    return 0;
}
