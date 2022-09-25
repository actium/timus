#include <iostream>
#include <map>
#include <vector>

struct Unit {
    size_t lb;
    size_t ub;
    unsigned k;
};

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<Unit> u;
    {
        std::map<unsigned, Unit> p;
        for (size_t i = 0; i < n; ++i) {
            unsigned h;
            std::cin >> h;

            const auto it = p.find(h);
            if (it == p.end()) {
                p[h] = { i, i, 1 };
            } else {
                it->second.ub = i;
                ++it->second.k;
            }
        }

        for (const auto& e : p)
            u.push_back(e.second);
    }

    std::pair<size_t, unsigned long long> d1 = { 0, 0 }, d2 = { 0, 0 };
    for (const Unit& x : u) {
        const unsigned long long c1 = d1.second + std::abs(int(x.ub - d1.first)) + (x.ub - x.lb) + x.k;
        const unsigned long long c2 = d2.second + std::abs(int(x.ub - d2.first)) + (x.ub - x.lb) + x.k;

        const unsigned long long c3 = d1.second + std::abs(int(x.lb - d1.first)) + (x.ub - x.lb) + x.k;
        const unsigned long long c4 = d2.second + std::abs(int(x.lb - d2.first)) + (x.ub - x.lb) + x.k;

        d1 = { x.lb, std::min(c1, c2) };
        d2 = { x.ub, std::min(c3, c4) };
    }

    std::cout << std::min(d1.second, d2.second) << '\n';

    return 0;
}
