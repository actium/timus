#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

class Matching {
public:
    explicit Matching(size_t size)
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
            std::vector<bool> v(size);
            traverse(i, v);
        }

        return matches_;
    }

private:
    bool traverse(size_t u, std::vector<bool>& v)
    {
        if (v[u])
            return false;

        v[u] = true;

        for (const size_t x : graph_[u]) {
            if (matches_[x] == -1 || traverse(matches_[x], v)) {
                matches_[x] = u;
                return true;
            }
        }
        return false;
    }

private:
    std::vector<std::vector<size_t>> graph_;
    std::vector<int> matches_;

}; // class Matching

void solve(unsigned a, unsigned b, const std::array<std::vector<unsigned>, 2>& t)
{
    const size_t n = t[0].size();

    Matching matching(n);
    for (size_t i = 0; i < n; ++i) {
        const auto ub = std::upper_bound(t[1].begin(), t[1].end(), t[0][i] + b);
        for (auto it = std::upper_bound(t[1].begin(), t[1].end(), t[0][i]); it != ub; ++it)
            matching.add_edge(i, it - t[1].begin());

        const auto lb = std::lower_bound(t[1].begin(), t[1].end(), t[0][i] + a);
        for (auto it = lb; it != t[1].end(); ++it)
            matching.add_edge(i, it - t[1].begin());
    }

    const std::vector<int>& matches = matching();

    if (std::find(matches.begin(), matches.end(), -1) != matches.end()) {
        std::cout << "Liar" << '\n';
    } else {
        std::cout << "No reason" << '\n';

        for (size_t i = 0; i < n; ++i)
            std::cout << t[0][matches[i]] << ' ' << t[1][i] << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned a, b;
    std::cin >> a >> b;

    size_t n;
    std::cin >> n;

    std::array<std::vector<unsigned>, 2> t;
    for (size_t i = 0; i < n; ++i) {
        unsigned x, d;
        std::cin >> x >> d;

        t[d].push_back(x);
    }

    solve(a, b, t);

    return 0;
}
