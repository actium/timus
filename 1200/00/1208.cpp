#include <iostream>
#include <map>
#include <vector>

unsigned count(const std::vector<uint64_t>& c, uint32_t x)
{
    const size_t k = c.size();

    uint64_t y = 0;
    for (size_t i = 0; i < k; ++i) {
        const uint32_t m = 1 << i;
        if ((x & m) == 0)
            continue;

        if ((y & c[i]) != 0)
            return 0;

        y |= c[i];
    }
    return __builtin_popcount(x);
}

int main()
{
    size_t k;
    std::cin >> k;

    std::vector<uint64_t> c(k);

    std::map<std::string, size_t> p;
    for (size_t i = 0; i < k; ++i) {
        std::string x, y, z;
        std::cin >> x >> y >> z;

        p.emplace(x, p.size());
        p.emplace(y, p.size());
        p.emplace(z, p.size());

        c[i] |= uint64_t(1) << p[x];
        c[i] |= uint64_t(1) << p[y];
        c[i] |= uint64_t(1) << p[z];
    }

    unsigned x = 0;
    for (uint32_t i = 1, ub = 1 << k; i < ub; ++i)
        x = std::max(x, count(c, i));
    
    std::cout << x << '\n';

    return 0;
}
