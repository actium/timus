#include <algorithm>
#include <iostream>
#include <vector>

#include <cstdint>

uint64_t hash(unsigned x, unsigned y)
{
    return static_cast<uint64_t>(x) << 17 | y;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    size_t m;
    std::cin >> m;

    std::vector<uint64_t> cs[51];
    for (size_t i = 0; i < m; ++i) {
        unsigned x, y, d;
        std::cin >> x >> y >> d;

        cs[d].push_back(hash(x, y));
    }

    std::vector<int> da(n+1);
    for (unsigned d = 2; d <= 50; ++d) {
        if (cs[d].empty())
            continue;

        std::sort(cs[d].begin(), cs[d].end());

        for (unsigned i = d; i <= n; ++i) {
            if (std::binary_search(cs[d].begin(), cs[d].end(), hash(a[i-1], a[i-d]))) {
                ++da[i-d];
                --da[i];
            }
        }
    }

    std::string t(n, '0');
    for (size_t i = 0; i < n; ++i) {
        t[i] += (da[i] != 0);
        da[i+1] += da[i];
    }

    std::cout << t << '\n';

    return 0;
}
