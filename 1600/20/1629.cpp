#include <algorithm>
#include <vector>

#include <cstdio>

struct Port {
    unsigned d;
    unsigned t;

    std::vector<unsigned> v;
};

unsigned solve(const std::vector<Port>& ps)
{
    const size_t n = ps.size();

    unsigned t = 0;
    for (size_t i = 1; i < n; ++i) {
        std::vector<unsigned> v;
        for (const unsigned x : ps[i].v) {
            if (t >= 1440 && x + ps[i].d >= 1440)
                v.push_back((x + ps[i].d) % 1440);

            v.push_back(x + ps[i].d);
            v.push_back(x + ps[i].d + 1440);
        }

        std::sort(v.begin(), v.end());

        const auto it = std::lower_bound(v.begin(), v.end(), t % 1440);
        t += *it - t % 1440 + ps[i].t;
    }
    return t;
}

int main()
{
    unsigned n;
    scanf("%u", &n);

    std::vector<Port> ps(n);
    for (unsigned i = 1; i < n; ++i) {
        unsigned q, d, t;
        scanf("%u %u %u", &q, &ps[i].d, &ps[i].t);

        for (unsigned j = 0; j < q; ++j) {
            unsigned h, m;
            scanf("%02u:%02u", &h, &m);

            ps[i].v.push_back(h * 60 + m);
        }
    }

    printf("%u\n", solve(ps));

    return 0;
}
