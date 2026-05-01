#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using graph_t = std::vector<unsigned>;

constexpr unsigned oo = ~0u;

class Matching {
public:
    Matching(size_t size)
        : graph_(size)
        , matches_(size, -1)
    {}

    void add_edge(size_t u, size_t v)
    {
        graph_[u].push_back(v);
    }

    const std::vector<int>& operator ()()
    {
        const size_t size = graph_.size();

        for (size_t i = 0; i < size; ++i) {
            std::vector<bool> used(size);
            search(i, used);
        }
        return matches_;
    }

private:
    bool search(size_t u, std::vector<bool>& used)
    {
        if (used[u])
            return false;

        used[u] = true;

        for (const size_t v : graph_[u]) {
            if (matches_[v] == -1 || search(matches_[v], used)) {
                matches_[v] = static_cast<int>(u);
                return true;
            }
        }
        return false;
    }

private:
    std::vector<std::vector<size_t>> graph_;
    std::vector<int> matches_;

}; // class Matching

std::vector<size_t> decompose(unsigned mask)
{
    std::vector<size_t> s;
    while (mask != 0) {
        s.push_back(__builtin_ctz(mask));
        mask &= mask - 1;
    }
    return s;
}

struct State {
    unsigned s;
    unsigned t = oo;
    std::vector<int> x;
};

std::vector<std::vector<std::pair<size_t, size_t>>> solve(const graph_t& g, size_t s)
{
    const size_t n = g.size(), m = 1 << n;

    std::vector<State> dp(m);

    const auto relax = [&](unsigned mask, unsigned s, unsigned t, const std::vector<int>& x) {
        if (t < dp[mask].t) {
            dp[mask].s = s;
            dp[mask].t = t;
            dp[mask].x = x;
        }
    };

    relax(1 << s, 0, 0, {});
    for (unsigned mask = 1 << s; mask < m; ++mask) {
        if (dp[mask].t == oo)
            continue;

        unsigned k = __builtin_popcount(mask), u = unsigned(m - 1) ^ mask;

        const std::vector<size_t> lhs = decompose(mask);
        for (unsigned x = u; x != 0; x = (x - 1) & u) {
            if (__builtin_popcount(x) > k)
                continue;

            const std::vector<size_t> rhs = decompose(x);

            Matching matching(n);
            for (const size_t u : lhs) {
                for (const size_t v : rhs) {
                    if ((g[u] & 1 << v) != 0)
                        matching.add_edge(u, v);
                }
            }

            const auto& match = matching();

            const auto c = n - std::count(match.begin(), match.end(), -1);
            if (c == __builtin_popcount(x))
                relax(mask | x, mask, dp[mask].t + 1, match);
        }
    }

    std::vector<std::vector<std::pair<size_t, size_t>>> certificate;
    for (auto mask = m - 1; !dp[mask].x.empty(); mask = dp[mask].s) {
        certificate.emplace_back();
        for (size_t i = 0; i < n; ++i) {
            if (dp[mask].x[i] != -1)
                certificate.back().emplace_back(dp[mask].x[i], i);
        }
    }
    std::reverse(certificate.begin(), certificate.end());
    return certificate;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::string> s;

    const auto index = [&](const std::string& p) -> size_t {
        const auto it = std::find(s.begin(), s.end(), p);
        if (it != s.end())
            return it - s.begin();

        s.push_back(p);
        return s.size() - 1;
    };

    size_t m;
    std::cin >> m;

    graph_t g(n);
    for (size_t i = 0; i < m; ++i) {
        std::string u, v;
        std::cin >> u >> v;

        g[index(u)] |= 1 << index(v);
        g[index(v)] |= 1 << index(u);
    }

    std::string a;
    std::cin >> a;

    const auto p = solve(g, index(a));

    std::cout << p.size() << '\n';
    for (const auto& v : p) {
        std::cout << v.size() << '\n';
        for (const auto& [i, j] : v)
            std::cout << s[i] << ' ' << s[j] << '\n';
    }

    return 0;
}
