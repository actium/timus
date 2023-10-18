#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;
using route_t = std::pair<unsigned, unsigned>;

constexpr int M = 18;

std::vector<unsigned> depths;
std::vector<std::vector<unsigned>> jumps;

void prepare(const graph_t& g, size_t u, size_t p)
{
    depths[u] = depths[p] + 1;

    jumps[u].resize(M);
    jumps[u][0] = p;
    for (int i = 1; i < M; ++i)
        jumps[u][i] = jumps[jumps[u][i-1]][i-1];

    for (const size_t v : g[u]) {
        if (v != p)
            prepare(g, v, u);
    }
}

size_t lca(size_t u, size_t v)
{
    if (depths[v] < depths[u])
        std::swap(u, v);

    for (int i = M - 1; i >= 0; --i) {
        if (depths[jumps[v][i]] >= depths[u])
            v = jumps[v][i];
    }

    if (v == u)
        return v;

    for (int i = M - 1; i >= 0; --i) {
        if (jumps[v][i] != jumps[u][i]) {
            v = jumps[v][i];
            u = jumps[u][i];
        }
    }
    return jumps[v][0];
}

class SegmentTree {
public:
    explicit SegmentTree(const std::vector<size_t>& data)
        : size_(data.size())
    {
        data_.reserve(2 * size_);
        data_.resize(size_);
        data_.insert(data_.end(), data.begin(), data.end());

        for (size_t i = size_ - 1; i > 0; --i)
            data_[i] = combine(data_[i<<1|0], data_[i<<1|1]);
    }

    size_t query(size_t lower_bound, size_t upper_bound) const
    {
        size_t lb = size_ + lower_bound, left = data_[lb++];
        if (lower_bound == upper_bound)
            return left;

        size_t ub = size_ + upper_bound, right = data_[--ub];
        while (lb < ub) {
            if (lb & 1)
                left = combine(left, data_[lb++]);

            if (ub & 1)
                right = combine(right, data_[--ub]);

            lb >>= 1, ub >>= 1;
        }

        return combine(left, right);
    }

private:
    static size_t combine(size_t u, size_t v)
    {
        if (depths[u] < depths[v])
            return u;

        if (depths[v] < depths[u])
            return v;

        return std::min(u, v);
    }

private:
    const size_t size_;

    std::vector<size_t> data_;

}; // class SegmentTree

void solve(const graph_t& g, const std::vector<route_t>& r)
{
    const size_t n = g.size();

    depths.resize(n);
    jumps.resize(n);

    prepare(g, 0, 0);

    std::vector<size_t> d(n);
    for (size_t i = 1; i < n; ++i)
        d[i] = lca(i-1, i);

    SegmentTree st(d);
    for (const route_t& q : r) {
        if (q.first == q.second)
            std::cout << q.first << '\n';
        else
            std::cout << 1 + st.query(q.first, q.second) << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    graph_t g(n);
    for (size_t i = 1; i < n; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u-1].push_back(v-1);
        g[v-1].push_back(u-1);
    }

    size_t q;
    std::cin >> q;

    std::vector<route_t> r(q);
    for (size_t i = 0; i < q; ++i)
        std::cin >> r[i].first >> r[i].second;

    solve(g, r);

    return 0;
}
