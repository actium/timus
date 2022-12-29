#include <iostream>
#include <map>

int main()
{
    size_t n;
    std::cin >> n;

    unsigned p;
    std::cin >> p;

    std::map<unsigned, unsigned> f;
    for (size_t i = 0; i < n; ++i) {
        unsigned x;
        std::cin >> x;

        ++f[x];
    }

    unsigned c = 0, q = 0;
    for (auto it = f.begin(); ; ) {
        unsigned k = 0;
        while (it != f.end() && it->first * (k + it->second) <= p) {
            k += it->second;
            ++it;
        }

        if (k == 0)
            break;

        c += k;
        ++q;
    }

    std::cout << c << ' ' << q << '\n';

    return 0;
}
