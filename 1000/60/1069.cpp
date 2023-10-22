#include <algorithm>
#include <iostream>
#include <vector>

void solve(const std::vector<unsigned>& c)
{
    const size_t n = c.size() + 1;

    std::vector<int> f(1 + n);
    for (const unsigned x : c)
        ++f[x];

    std::vector<std::vector<unsigned>> g(1 + n);
    unsigned x = 1;
    for (const unsigned q : c) {
        while (f[x] != 0)
            ++x;

        g[q].push_back(x);
        g[x].push_back(q);

        --f[x];
        if (--f[q] == 0 && q < x)
            x = q;
    }

    for (unsigned i = 1; i <= n; ++i) {
        std::sort(g[i].begin(), g[i].end());

        std::cout << i << ':';
        for (const unsigned u : g[i])
            std::cout << ' ' << u;
        std::cout << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<unsigned> c;
    for (unsigned x; std::cin >> x; c.push_back(x));

    solve(c);

    return 0;
}
