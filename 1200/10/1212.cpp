#include <algorithm>
#include <iostream>
#include <vector>

struct Ship {
    unsigned x;
    unsigned y;
    unsigned k;
    char t;
};

unsigned count(std::vector<unsigned>& p, unsigned k)
{
    std::sort(p.begin(), p.end());
    p.erase(std::unique(p.begin(), p.end()), p.end());

    unsigned q = 0;
    for (size_t i = 1; i < p.size(); ++i) {
        const unsigned d = p[i] - p[i-1] - 1;
        if (d >= k)
            q += d - k + 1;
    }
    return q;
}

unsigned solve(unsigned n, unsigned m, const std::vector<Ship>& s, unsigned k)
{
    unsigned v = 0;

    for (unsigned y = 1; y <= n; ++y) {
        std::vector<unsigned> p = { 0, m + 1 };
        for (const Ship& q : s) {
            switch (q.t) {
                case 'H':
                    if (q.y >= y - 1 && q.y <= y + 1) {
                        p.push_back(q.x - 1);
                        for (unsigned i = 0; i <= q.k; ++i)
                            p.push_back(q.x + i);
                    }
                    break;
                case 'V':
                    if (q.y <= y + 1 && q.y + q.k >= y) {
                        p.push_back(q.x - 1);
                        p.push_back(q.x);
                        p.push_back(q.x + 1);
                    }
                    break;
            }
        }

        v += count(p, k);
    }

    for (unsigned x = 1; x <= m; ++x) {
        std::vector<unsigned> p = { 0, n + 1 };
        for (const Ship& q : s) {
            switch (q.t) {
                case 'H':
                    if (q.x <= x + 1 && q.x + q.k >= x) {
                        p.push_back(q.y - 1);
                        p.push_back(q.y);
                        p.push_back(q.y + 1);
                    }
                    break;
                case 'V':
                    if (q.x >= x - 1 && q.x <= x + 1) {
                        p.push_back(q.y - 1);
                        for (unsigned i = 0; i <= q.k; ++i)
                            p.push_back(q.y + i);
                    }
                    break;
            }
        }

        v += count(p, k);
    }

    return k == 1 ? v / 2 : v;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m, q;
    std::cin >> n >> m >> q;

    std::vector<Ship> s(q);
    for (unsigned i = 0; i < q; ++i)
        std::cin >> s[i].x >> s[i].y >> s[i].k >> s[i].t;

    unsigned k;
    std::cin >> k;

    std::cout << solve(n, m, s, k) << '\n';

    return 0;
}
