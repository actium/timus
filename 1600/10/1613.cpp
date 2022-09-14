#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

char search(const std::map<unsigned, std::vector<unsigned>>& m, unsigned l, unsigned r, unsigned x)
{
    const auto it = m.find(x);
    if (it == m.cend())
        return '0';

    const auto jt = std::lower_bound(it->second.cbegin(), it->second.cend(), l);
    if (jt == it->second.cend() || *jt > r)
        return '0';

    return '1';
}

int main()
{
    size_t n;
    std::cin >> n;

    std::map<unsigned, std::vector<unsigned>> m;
    for (size_t i = 0; i < n; ++i) {
        unsigned x;
        std::cin >> x;

        m[x].push_back(1 + i);
    }

    for (std::pair<const unsigned, std::vector<unsigned>>& e : m)
        std::sort(e.second.begin(), e.second.end());

    unsigned q;
    std::cin >> q;

    for (unsigned i = 0; i < q; ++i) {
        unsigned l, r, x;
        std::cin >> l >> r >> x;

        std::cout << search(m, l, r, x);
    }

    return 0;
}
