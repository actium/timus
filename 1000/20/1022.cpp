#include <iostream>
#include <vector>

void solve(const std::vector<std::vector<size_t>>& g)
{
    const size_t n = g.size();

    std::vector<unsigned> d(n);
    for (const auto& c : g) {
        for (const size_t v : c)
            ++d[v];
    }

    std::vector<size_t> o;
    for (size_t i = 0; i < n; ++i) {
        if (d[i] == 0)
            o.push_back(i);
    }

    for (size_t i = 0; i < o.size(); ++i) {
        for (const size_t v : g[o[i]]) {
            if (--d[v] == 0)
                o.push_back(v);
        }
    }

    for (size_t i = n-1; i > 0; --i)
        std::cout << 1 + o[i] << ' ';
    std::cout << 1 + o[0] << '\n';
}

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<std::vector<size_t>> g(n);
    for (size_t i = 0; i < n; ++i) {
        for (unsigned x; std::cin >> x && x != 0; g[x-1].push_back(i));
    }

    solve(g);

    return 0;
}
