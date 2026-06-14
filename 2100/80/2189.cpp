#include <iostream>
#include <map>
#include <set>
#include <vector>

#include <cassert>

using integer = unsigned long long;

integer count(unsigned w)
{
    return w * integer(w + 1) / 2;
}

size_t compress(std::vector<unsigned>& a, std::vector<std::pair<unsigned, unsigned>>& rs)
{
    const size_t n = a.size(), q = rs.size();

    std::map<unsigned, unsigned> x;
    for (size_t i = 0; i < n; ++i) {
        const auto it = x.emplace(a[i], x.size()).first;
        a[i] = it->second;
    }
    for (size_t i = 0; i < q; ++i) {
        const auto it = x.emplace(rs[i].second, x.size()).first;
        rs[i].second = it->second;
    }
    return x.size();
}

void solve(std::vector<unsigned>& a, std::vector<std::pair<unsigned, unsigned>>& rs)
{
    const size_t n = a.size(), m = compress(a, rs);

    std::vector<std::set<unsigned>> ps(m, { 0, n+1 });
    std::vector<integer> ws(m, count(n));

    std::map<integer, unsigned> h;
    h[count(n)] = m;

    const auto insert = [&](unsigned p, unsigned v) {
        const auto s = ps[v].insert(p);
        assert(s.second);

        const auto it = s.first;
        assert(it != ps[v].begin() && it != ps[v].end());

        if (--h[ws[v]] == 0)
            h.erase(ws[v]);

        ws[v] -= count(*std::next(it) - *std::prev(it) - 1);
        ws[v] += count(p - *std::prev(it) - 1);
        ws[v] += count(*std::next(it) - p - 1);

        ++h[ws[v]];
    };

    const auto remove = [&](unsigned p, unsigned v) {
        const auto it = ps[v].find(p);
        assert(it != ps[v].begin() && it != ps[v].end());

        if (--h[ws[v]] == 0)
            h.erase(ws[v]);

        ws[v] -= count(p - *std::prev(it) - 1);
        ws[v] -= count(*std::next(it) - p - 1);
        ws[v] += count(*std::next(it) - *std::prev(it) - 1);

        ++h[ws[v]];

        ps[v].erase(it);
    };

    for (size_t i = 0; i < n; ++i)
        insert(1 + i, a[i]);

    for (const auto& [x, v] : rs) {
        if (a[x-1] != v) {
            remove(x, a[x-1]);
            a[x-1] = v;
            insert(x, a[x-1]);
        }
        std::cout << h.begin()->first << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, q;
    std::cin >> n >> q;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::vector<std::pair<unsigned, unsigned>> rs(q);
    for (size_t i = 0; i < q; ++i)
        std::cin >> rs[i].first >> rs[i].second;

    solve(a, rs);

    return 0;
}
