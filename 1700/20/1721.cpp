#include <iostream>
#include <string>
#include <vector>

struct Creator {
    std::string name;
    std::string spec;
    unsigned rank;
};

class Matching {
public:
    Matching(size_t lsize, size_t rsize)
        : graph_(lsize)
        , matches_(rsize, -1)
    {}

    void add_edge(size_t u, size_t v)
    {
        graph_[u].push_back(v);
    }

    const std::vector<int> operator ()()
    {
        const size_t lsize = graph_.size();

        for (size_t i = 0; i < lsize; ++i) {
            std::vector<bool> v(lsize);
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

std::vector<std::pair<size_t, size_t>> solve(const std::vector<Creator>& c)
{
    const size_t n = c.size();

    std::vector<size_t> p[2];
    for (size_t i = 0; i < n; ++i)
        p[c[i].rank % 4 < 2].push_back(i);

    Matching matching(p[0].size(), p[1].size());
    for (size_t i = 0; i < p[0].size(); ++i) {
        const size_t u = p[0][i];

        for (size_t j = 0; j < p[1].size(); ++j) {
            const size_t v = p[1][j];
            if (c[u].spec[0] == c[v].spec[0] && c[u].spec[0] != 'a')
                continue;

            const unsigned d = std::max(c[u].rank, c[v].rank) - std::min(c[u].rank, c[v].rank);
            if (d == 2)
                matching.add_edge(i, j);
        }
    }

    const std::vector<int> matches = matching();

    std::vector<std::pair<size_t, size_t>> s;
    for (size_t i = 0; i < p[1].size(); ++i) {
        const int x = matches[i];
        if (x == -1)
            continue;

        s.emplace_back(p[0][x], p[1][i]);

        if (c[s.back().first].spec[0] == 't' || c[s.back().second].spec[0] == 's')
            std::swap(s.back().first, s.back().second);
    }
    return s;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Creator> c(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> c[i].name >> c[i].spec >> c[i].rank;

    const std::vector<std::pair<size_t, size_t>> s = solve(c);

    std::cout << s.size() << '\n';
    for (const std::pair<size_t, size_t>& e : s)
        std::cout << c[e.first].name << ' ' << c[e.second].name << '\n';

    return 0;
}
