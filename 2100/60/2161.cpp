#include <iostream>
#include <vector>

struct Knight {
    unsigned a;
    unsigned d;
    unsigned g;
};

int solve(const std::vector<Knight>& ks)
{
    const size_t n = ks.size();

    std::vector<unsigned> pa(1 + n), sa(1 + n), pd(1 + n), sd(1 + n);
    for (size_t i = 0; i < n; ++i) {
        pa[i+1] = std::max(pa[i], ks[i].a + ks[i].g);
        pd[i+1] = std::max(pd[i], ks[i].d + ks[i].g);
        sa[n-i-1] = std::max(sa[n-i], ks[n-i-1].a + ks[n-i-1].g);
        sd[n-i-1] = std::max(sd[n-i], ks[n-i-1].d + ks[n-i-1].g);
    }

    for (size_t i = 0; i < n; ++i) {
        const unsigned ra = std::max(pd[i], sd[i+1]), rd = std::max(pa[i], sa[i+1]) + 1;
        const unsigned da = ks[i].a < ra ? ra - ks[i].a : 0, dd = ks[i].d < rd ? rd - ks[i].d : 0;
        if (da + dd <= ks[i].g)
            return i + 1;
    }

    return -1;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Knight> ks(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> ks[i].a >> ks[i].d >> ks[i].g;

    std::cout << solve(ks) << '\n';

    return 0;
}
