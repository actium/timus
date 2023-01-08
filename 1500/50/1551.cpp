#include <iostream>
#include <map>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned n;
    std::cin >> n;

    const unsigned k = 1 << n;

    std::map<std::string, unsigned> f;
    for (unsigned i = k; i != 0; --i) {
        std::string x, p;
        std::cin >> x >> p;

        ++f[p];
    }

    unsigned q = 0;
    for (const auto& e : f)
        q = std::max(q, e.second);

    std::cout << 31 - __builtin_clz(k / q) << '\n';

    return 0;
}
