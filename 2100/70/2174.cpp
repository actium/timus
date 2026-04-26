#include <iostream>
#include <vector>

using graph_t = std::vector<std::vector<size_t>>;

class Matching {
public:
    explicit Matching(size_t p_size)
        : graph_(p_size)
        , matches_(p_size, -1)
    {}

    void add_edge(size_t u, size_t v)
    {
        graph_[u].push_back(v);
    }

    const std::vector<int> operator ()()
    {
        const size_t p_size = graph_.size();

        for (size_t i = 0; i < p_size; ++i) {
            std::vector<bool> used(p_size);
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
                matches_[v] = u;
                return true;
            }
        }
        return false;
    }

private:
    std::vector<std::vector<size_t>> graph_;
    std::vector<int> matches_;

}; // class Matching

bool test_primality(unsigned x)
{
    for (unsigned i = 2; i * i <= x; ++i) {
        if (x % i == 0)
            return false;
    }
    return x != 1;
}

void solve(const std::vector<unsigned>& c)
{
    const size_t n = c.size();

    std::vector<size_t> p[3];
    for (size_t i = 0; i < n; ++i) {
        const size_t x = c[i] % 2 + (c[i] == 1);
        p[x].push_back(i);
    }

    const size_t p_size = std::max(p[0].size(), p[1].size());
    for (size_t i = 0; i < 2; ++i) {
        while (!p[2].empty() && p[i].size() < p_size) {
            p[i].push_back(p[2].back());
            p[2].pop_back();
        }
    }

    Matching matching(p_size);
    for (size_t i = 0; i < p[0].size(); ++i) {
        for (size_t j = 0; j < p[1].size(); ++j) {
            if (test_primality(c[p[0][i]] + c[p[1][j]]))
                matching.add_edge(i, j);
        }
    }

    const auto matches = matching();

    std::vector<std::pair<unsigned, unsigned>> s;
    for (size_t i = 0; i < p_size; ++i) {
        if (matches[i] != -1)
            s.emplace_back(p[0][matches[i]], p[1][i]);
    }

    for (size_t i = 1; i < p[2].size(); i += 2)
        s.emplace_back(p[2][i-1], p[2][i]);

    if (2 * s.size() != n) {
        std::cout << "NO" << '\n';
    } else {
        std::cout << "YES" << '\n';
        for (const auto& [u, v] : s)
            std::cout << c[u] << ' ' << c[v] << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> c(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> c[i];

    solve(c);

    return 0;
}
