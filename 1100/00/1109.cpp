#include <iostream>
#include <vector>

bool match(const std::vector<std::vector<size_t>>& g, size_t i, std::vector<bool>& v, std::vector<int>& t)
{
    if (v[i])
        return false;

    v[i] = true;
    for (const size_t j : g[i]) {
        if (t[j] == -1 || match(g, t[j], v, t)) {
            t[j] = i;
            return true;
        }
    }
    return false;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::vector<size_t>> g(n);
    for (size_t i = 0; i < k; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        g[u-1].push_back(v-1);
    }

    std::vector<int> t(m, -1);
    for (size_t i = 0; i < n; ++i) {
        std::vector<bool> v(n);
        match(g, i, v, t);
    }

    unsigned q = 0;
    for (size_t i = 0; i < m; ++i)
        q += (t[i] != -1);

    std::cout << n + m - q << '\n';

    return 0;
}
