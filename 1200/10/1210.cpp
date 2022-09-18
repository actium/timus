#include <iostream>
#include <vector>

constexpr int oo = 10000000;

struct Node {
    bool v = false;
    std::vector<std::pair<size_t, int>> s;
    int c = oo;
};

int traverse(std::vector<std::vector<Node>>& nodes, size_t i, size_t j)
{
    if (!nodes[i][j].v) {
        for (const std::pair<size_t, int>& x : nodes[i][j].s)
            nodes[i][j].c = std::min(nodes[i][j].c, traverse(nodes, i-1, x.first) + x.second);

        nodes[i][j].v = true;
    }
    return nodes[i][j].c;
}

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<std::vector<Node>> nodes(1+n);
    nodes[0].push_back({ true, {}, 0 });

    for (size_t i = 0; i < n; ++i) {
        size_t k;
        std::cin >> k;

        nodes[1+i].resize(k);
        for (size_t j = 0; j < k; ++j) {
            unsigned x;
            for (std::cin >> x; x != 0; std::cin >> x) {
                int c;
                std::cin >> c;

                nodes[1+i][j].s.emplace_back(x-1, c);
            }
        }

        char d;
        std::cin >> d;
    }

    int b = oo;
    for (size_t i = 0, k = nodes[n].size(); i < k; ++i)
        b = std::min(b, traverse(nodes, n, i));

    std::cout << b << '\n';

    return 0;
}
