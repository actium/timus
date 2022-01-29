#include <iostream>
#include <unordered_set>

int main()
{
    unsigned n;
    std::cin >> n;

    std::unordered_set<unsigned> s;
    while (n-- > 0) {
        unsigned x;
        std::cin >> x;

        s.insert(x);
    }

    unsigned m;
    std::cin >> m;

    unsigned q = 0;
    while (m-- > 0) {
        unsigned x;
        std::cin >> x;

        q += s.count(x);
    }

    std::cout << q << '\n';

    return 0;
}
