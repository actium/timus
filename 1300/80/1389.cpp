#include <iostream>
#include <vector>

using edge_t = std::pair<unsigned, unsigned>;

struct Node {
    unsigned id;

    std::vector<Node*> subnodes;

    unsigned k[2] = {};
    const Node* x = nullptr;
};

void prepare(Node* node, const Node* parent)
{
    for (Node* subnode : node->subnodes) {
        if (subnode != parent) {
            prepare(subnode, node);
            node->k[0] += subnode->k[1];
        }
    }

    node->k[1] = node->k[0];

    for (const Node* subnode : node->subnodes) {
        if (subnode == parent)
            continue;

        if (node->k[0] - subnode->k[1] + subnode->k[0] + 1 > node->k[1]) {
            node->k[1] = node->k[0] - subnode->k[1] + subnode->k[0] + 1;
            node->x = subnode;
        }
    }
}

void solve(const Node* node, const Node* parent, bool closing, std::vector<edge_t>& edges)
{
    if (closing && node->x != nullptr)
        edges.emplace_back(node->id, node->x->id);

    for (const Node* subnode : node->subnodes) {
        if (subnode != parent)
            solve(subnode, node, subnode != node->x, edges);
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<Node> nodes(n);
    for (size_t i = 0; i < n; ++i)
        nodes[i].id = i + 1;

    for (size_t i = 0; i < m; ++i) {
        unsigned u, v;
        std::cin >> u >> v;

        nodes[u-1].subnodes.push_back(&nodes[v-1]);
        nodes[v-1].subnodes.push_back(&nodes[u-1]);
    }

    prepare(&nodes[0], nullptr);

    std::vector<edge_t> edges;
    solve(&nodes[0], nullptr, nodes[0].k[1] > nodes[0].k[0], edges);

    std::cout << edges.size() << '\n';
    for (const edge_t& e : edges)
        std::cout << e.first << ' ' << e.second << '\n';

    return 0;
}
