#include <iostream>
#include <vector>

struct Node {
    size_t p;
    size_t k;
    unsigned v;

    Node(size_t p, size_t k, unsigned v)
        : p(p), k(k), v(v)
    {}
};

std::vector<unsigned> solve(const std::vector<unsigned>& c)
{
    size_t p[1 + 10000] = {};

    std::vector<Node> nodes;
    nodes.emplace_back(0, 0, 0);
    for (const unsigned x : c) {
        const Node& t = nodes[p[x]];
        if (t.k == 0 || t.k > nodes.back().k) {
            nodes.emplace_back(nodes.size() - 1, nodes.back().k + 1, x);
        } else {
            nodes.emplace_back(t.p, t.k, x);
        }
        p[x] = nodes.size() - 1;
    }

    std::vector<unsigned> q;
    for (const Node* x = &nodes[p[c.back()]]; x->k != 0; x = &nodes[x->p])
        q.push_back(x->v);

    return std::vector<unsigned>(q.rbegin(), q.rend());
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> c(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> c[i];

    for (const unsigned x : solve(c))
        std::cout << x << ' ';

    return 0;
}
