#include <iostream>
#include <queue>
#include <vector>

using edge_t = std::pair<unsigned, unsigned>;
using query_t = std::pair<unsigned, unsigned>;
using range_t = std::pair<unsigned, unsigned>;

constexpr unsigned M = 1000000007, oo = ~0u;

void decompose(const std::vector<std::vector<size_t>>& g, std::vector<size_t>& x, std::vector<size_t>& p, std::vector<range_t>& r)
{
    std::queue<size_t> q;

    unsigned t = 0;

    const auto enqueue = [&](size_t u, size_t v) {
        x[u] = t++;
        p[u] = v;

        q.push(u);
    };

    enqueue(0, oo);
    while (!q.empty()) {
        const size_t u = q.front();
        q.pop();

        const unsigned s = t;
        for (const size_t v : g[u]) {
            if (x[v] == oo)
                enqueue(v, x[u]);
        }

        r[u] = std::make_pair(s, t);
    }
}

class BinaryIndexedTree {
public:
    explicit BinaryIndexedTree(unsigned size)
        : data_(1 + size)
    {}

    void add(unsigned index, unsigned delta)
    {
        for (unsigned i = 1 + index; i < data_.size(); i += i & -i) {
            data_[i] += delta;
            data_[i] %= M;
        }
    }

    unsigned sum(unsigned index) const
    {
        unsigned v = 0;
        for (unsigned i = 1 + index; i > 0; i &= i - 1) {
            v += data_[i];
            v %= M;
        }
        return v;
    }

private:
    std::vector<unsigned> data_;

}; // class BinaryIndexedTree

void solve(const std::vector<unsigned>& a, const std::vector<edge_t>& e, std::vector<query_t>& q)
{
    const size_t n = a.size();

    std::vector<std::vector<size_t>> g(n);
    for (const edge_t& x : e) {
        g[x.first-1].push_back(x.second - 1);
        g[x.second-1].push_back(x.first - 1);
    }

    std::vector<size_t> x(n, oo), p(n);
    std::vector<range_t> r(n);
    decompose(g, x, p, r);

    BinaryIndexedTree bit(n + 1);
    for (size_t i = 0; i < n; ++i) {
        bit.add(x[i], a[i]);
        bit.add(x[i] + 1, M - a[i]);
    }

    for (const query_t& c : q) {
        if (c.first == 1) {
            const unsigned d = bit.sum(x[c.second - 1]);
            if (d == 0)
                continue;

            if (c.second != 1) {
                bit.add(p[c.second - 1], d);
                bit.add(p[c.second - 1] + 1, M - d);
            }

            if (r[c.second - 1].first != r[c.second - 1].second) {
                bit.add(r[c.second - 1].first, d);
                bit.add(r[c.second - 1].second, M - d);
            }
        } else {
            std::cout << bit.sum(x[c.second - 1]) << '\n';
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::vector<edge_t> e(n - 1);
    for (size_t i = 1; i < n; ++i)
        std::cin >> e[i-1].first >> e[i-1].second;

    size_t m;
    std::cin >> m;

    std::vector<query_t> q(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> q[i].first >> q[i].second;

    solve(a, e, q);

    return 0;
}
