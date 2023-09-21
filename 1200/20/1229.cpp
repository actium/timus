#include <iostream>
#include <vector>

class Matching {
public:
    explicit Matching(size_t size)
        : graph_(size), matches_(size, -1)
    {}

    void add_edge(size_t u, size_t v)
    {
        graph_[u].push_back(v);
        graph_[v].push_back(u);
    }

    const std::vector<int>& operator ()()
    {
        const size_t size = graph_.size();

        for (size_t i = 0; i < size; ++i) {
            std::vector<bool> used(size);
            traverse(i, used);
        }

        return matches_;
    }

private:
    bool traverse(size_t v, std::vector<bool>& used)
    {
        if (used[v])
            return false;

        used[v] = true;

        for (const size_t u : graph_[v]) {
            if (matches_[u] == -1 || traverse(matches_[u], used)) {
                matches_[u] = v;
                return true;
            }
        }
        return false;
    }

private:
    std::vector<std::vector<size_t>> graph_;
    std::vector<int> matches_;

}; // class Matching

void fill(size_t u, size_t& k, const std::vector<int>& matches, std::vector<std::vector<unsigned>>& c)
{
    const size_t m = c[0].size(), i = u / m, j = u - i * m;
    if (c[i][j] != 0)
        return;

    c[i][j] = ++k / 2;

    fill(matches[u], k, matches, c);
}

void solve(const std::vector<std::vector<unsigned>>& b)
{
    const size_t n = b.size(), m = b[0].size();

    Matching matching(n * m);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            if (i > 0 && b[i][j] != b[i-1][j]) {
                const size_t u = m * (i - 1) + j;
                matching.add_edge(u, u + m);
            }
            if (j > 0 && b[i][j] != b[i][j-1]) {
                const size_t u = m * i + j - 1;
                matching.add_edge(u, u + 1);
            }
        }
    }

    const std::vector<int>& matches = matching();
    for (const int x : matches) {
        if (x == -1) {
            std::cout << -1 << '\n';
            return;
        }
    }

    std::vector<std::vector<unsigned>> c(n, std::vector<unsigned>(m));
    for (size_t i = 0, k = 1; i < n * m; ++i)
        fill(i, k, matches, c);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            std::cout << c[i][j] << ' ';

        std::cout << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<unsigned>> b(n, std::vector<unsigned>(m));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            std::cin >> b[i][j];
    }

    solve(b);

    return 0;
}
