#include <algorithm>
#include <iostream>
#include <vector>

#include <cassert>

using graph_t = std::vector<std::vector<unsigned>>;

constexpr unsigned oo = ~0u;

struct State {
    unsigned sum = 0;
    std::vector<std::pair<unsigned, unsigned>> candidates;

    void update(unsigned v, unsigned k1, unsigned k2)
    {
        if (v < sum)
            return;

        if (v > sum)
            candidates.clear();

        for (const auto& c : candidates) {
            if (c.first == k1 && c.second == k2)
                return;
        }

        sum = v;
        candidates.emplace_back(k1, k2);
    }
};

void solve(const graph_t& g, const std::vector<unsigned>& a)
{
    const size_t n = g.size(), k = a.size();

    std::vector<std::pair<unsigned, unsigned>> distances(n, { oo, oo }), q;

    const auto enqueue = [&](unsigned u, unsigned d) {
        unsigned& w = (d % 2 == 1 ? distances[u].first : distances[u].second);
        if (d < w) {
            w = d;
            q.emplace_back(u, d);
        }
    };

    enqueue(1, 0);

    for (size_t i = 0; i < q.size(); ++i) {
        for (const auto v : g[q[i].first])
            enqueue(v, q[i].second + 1);
    }

    std::vector<unsigned> c[2];
    for (const unsigned x : a)
        c[x%2].push_back(x);

    for (size_t i = 0; i < 2; ++i)
        std::sort(c[i].begin(), c[i].end(), std::greater<unsigned>());

    std::vector<State> dp[2];
    for (size_t i = 0; i < 2; ++i) {
        dp[i].resize(1 + k);
        dp[i][0].update(0, 0, 0);
    }
    for (size_t i = 1; i <= k; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            for (const auto& candidate : dp[j][i-1].candidates) {
                if (candidate.first < c[0].size()) {
                    const auto sum = dp[j][i-1].sum + c[0][candidate.first];
                    dp[sum%2][i].update(sum, candidate.first + 1, candidate.second);
                }
                if (candidate.second < c[1].size()) {
                    const auto sum = dp[j][i-1].sum + c[1][candidate.second];
                    dp[sum%2][i].update(sum, candidate.first, candidate.second + 1);
                }
            }
        }
    }

    unsigned s = 0;
    for (size_t i = 1; i < n; ++i) {
        assert(distances[i].first != oo || distances[i].second != oo);

        if (distances[i].first != oo)
            s = std::max(s, distances[i].first);
        if (distances[i].second != oo)
            s = std::max(s, distances[i].second);
    }

    std::vector<unsigned> t(1+s+1, oo);
    t[0] = 0;
    for (unsigned i = 1; i <= k; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            unsigned x = dp[j][i].sum;
            if (x > s)
                x = s + (x % 2 != s % 2);

            t[x] = std::min(t[x], i);
        }
    }

    for (size_t i = s + 1; i > 1; --i)
        t[i-2] = std::min(t[i-2], t[i]);

    for (size_t i = 1; i < n; ++i) {
        unsigned k = oo;
        if (distances[i].first != oo)
            k = std::min(k, t[distances[i].first]);
        if (distances[i].second != oo)
            k = std::min(k, t[distances[i].second]);

        std::cout << static_cast<int>(k) << " \n"[i+1==n];
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m, k;
    std::cin >> n >> m >> k;

    graph_t g(1+n);
    for (size_t i = 0; i < m; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<unsigned> a(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> a[i];

    solve(g, a);

    return 0;
}
