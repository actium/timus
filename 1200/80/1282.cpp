#include <iostream>
#include <vector>

struct Node {
    std::vector<size_t> subnodes;
    int value = -1;
};

int solve(std::vector<Node>& g, size_t x, int m)
{
    if (g[x].subnodes.empty())
        return g[x].value;

    int value = -m;
    for (const size_t v : g[x].subnodes) {
        const int t = solve(g, v, -m);
        value = m < 0 ? std::min(value, t) : std::max(value, t);
    }
    return value;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Node> g(n);
    for (size_t i = 1; i < n; ++i) {
        char t;
        std::cin >> t;

        unsigned p;
        std::cin >> p;

        if (t == 'L')
            std::cin >> g[i].value;

        g[p-1].subnodes.push_back(i);
    }

    constexpr const char* s[3] = {"-1", "0", "+1"};
    std::cout << s[solve(g, 0, 1) + 1] << '\n';

    return 0;
}
