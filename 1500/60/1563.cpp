#include <iostream>
#include <unordered_set>

int main()
{
    std::unordered_set<std::string> s;

    unsigned n;
    std::cin >> n;
    std::cin.ignore();

    unsigned q = 0;
    while (n-- > 0) {
        std::string x;
        std::getline(std::cin, x);

        q += s.count(x);
        s.insert(x);
    }

    std::cout << q << '\n';

    return 0;
}
