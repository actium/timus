#include <iostream>
#include <vector>

constexpr unsigned oo = ~0u;

unsigned set()
{
    size_t k;
    std::cin >> k;

    unsigned s = 0;
    for (size_t i = 0; i < k; ++i) {
        unsigned x;
        std::cin >> x;

        s |= 1 << (x - 1);
    }
    return s;
}

void solve(const std::vector<std::pair<unsigned, unsigned>>& s, unsigned t, std::vector<unsigned>& v)
{
    for (const std::pair<unsigned, unsigned>& x : s) {
        if ((t & x.first) == 0)
            continue;

        if ((x.first & t) == t) {
            v[t] = std::min(v[t], x.second);
            continue;
        }

        const unsigned u = t & ~x.first;
        if (v[u] == oo)
            solve(s, u, v);

        v[t] = std::min(v[t], x.second + v[u]);
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::pair<unsigned, unsigned>> s(n);
    for (size_t i = 0; i < n; ++i) {
        s[i].first = 1 << i;
        std::cin >> s[i].second;
    }

    size_t m;
    std::cin >> m;

    s.resize(n + m);
    for (size_t i = 0; i < m; ++i) {
        std::cin >> s[n + i].second;
        s[n + i].first = set();
    }

    const unsigned t = set();

    std::vector<unsigned> v(1 << n, oo);
    solve(s, t, v);

    std::cout << v[t] << '\n';

    return 0;
}
