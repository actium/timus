#include <iostream>
#include <vector>

void solve(const std::vector<unsigned>& w, const std::vector<unsigned>& t, unsigned k)
{
    const size_t n = w.size(), m = t.size();

    std::vector<unsigned> ps(1 + n);
    for (size_t i = 0; i < n; ++i)
        ps[i + 1] = ps[i] + w[i];

    unsigned x = 0, d = 0, lt = 0;
    for (const unsigned ts : t) {
        const unsigned q = ts - lt - 1;
        if (x + q < n) {
            const unsigned s = ps[x + q], t = s - std::min(s, k);
            x = std::lower_bound(ps.begin(), ps.end(), t) - ps.begin();
            x -= (x > 0);
            d += q + 1;
            lt = ts;
        } else {
            d += n - x;
            break;
        }
    }

    std::cout << d << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    unsigned k;
    std::cin >> k;

    std::vector<unsigned> w(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> w[i];

    std::vector<unsigned> t(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> t[i];

    t.push_back(~0u);
    solve(w, t, k);

    return 0;
}
