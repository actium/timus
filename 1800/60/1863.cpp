#include <algorithm>
#include <iostream>
#include <vector>

using integer = long long;

struct Candidate {
    integer lb = 0;
    integer ub = 0;
    integer x = 0;
};

std::vector<Candidate> process(const std::vector<unsigned>& d, size_t b, size_t e)
{
    const unsigned m = e - b, ub = 1 << m;

    std::vector<Candidate> cs(ub);
    for (unsigned mask = 0; mask < ub; ++mask) {
        for (unsigned i = 0; i < m; ++i) {
            if ((mask & 1 << i) != 0)
                cs[mask].x += d[b+i];
            else
                cs[mask].x -= d[b+i];

            cs[mask].lb = std::min(cs[mask].lb, cs[mask].x);
            cs[mask].ub = std::max(cs[mask].ub, cs[mask].x);
        }
    }
    return cs;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, s;
    std::cin >> n >> s;

    size_t k;
    std::cin >> k;

    std::vector<unsigned> d(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> d[i];

    const size_t m = (k + 1) / 2;

    const auto p = process(d, 0, m);
    const auto q = process(d, m, k);

    std::vector<unsigned> r;
    for (const auto& c : p) {
        if (s + c.lb >= 0 && s + c.ub <= n)
            r.push_back(s + c.x);
    }

    std::sort(r.begin(), r.end());
    r.erase(std::unique(r.begin(), r.end()), r.end());

    unsigned lb = ~0u, ub = 0;
    for (const auto& c : q) {
        if (r.back() + c.lb < 0 || r.front() + c.ub > n)
            continue;

        const auto it = std::lower_bound(r.begin(), r.end(), -c.lb);
        if (*it + c.ub <= n) {
            const unsigned x = *it + c.x;
            lb = std::min(lb, x);
            ub = std::max(ub, x);
        }

        const auto jt = std::prev(std::upper_bound(r.begin(), r.end(), n - c.ub));
        if (*jt + c.lb >= 0) {
            const unsigned x = *jt + c.x;
            lb = std::min(lb, x);
            ub = std::max(ub, x);
        }
    }

    std::cout << lb << ' ' << ub << '\n';

    return 0;
}
