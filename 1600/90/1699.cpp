#include <iostream>
#include <string>
#include <vector>

using graph_t = std::vector<std::vector<std::pair<unsigned, bool>>>;

struct Path {
    unsigned turn_count = 0;
    bool endmost_turn_types[2] = {};
    bool empty = true;

    Path() = default;

    explicit Path(bool vertical)
        : empty(false)
    {
        endmost_turn_types[0] = vertical;
        endmost_turn_types[1] = vertical;
    }

    Path(const Path& lhs, const Path& rhs)
    {
        if (lhs.empty || rhs.empty) {
            *this = (lhs.empty ? rhs : lhs);
        } else {
            turn_count = lhs.turn_count + rhs.turn_count;
            turn_count += (lhs.endmost_turn_types[1] != rhs.endmost_turn_types[0]);
            endmost_turn_types[0] = lhs.endmost_turn_types[0];
            endmost_turn_types[1] = rhs.endmost_turn_types[1];
            empty = false;
        }
    }

    Path reverse() const
    {
        Path path = *this;
        std::swap(path.endmost_turn_types[0], path.endmost_turn_types[1]);
        return path;
    }
};

struct LCA {
    std::vector<unsigned> depths;
    std::vector<std::vector<unsigned>> jumps;
    std::vector<std::vector<Path>> paths;

    LCA(const graph_t& tree, unsigned root)
    {
        const unsigned n = tree.size(), m = __builtin_clz(1) - __builtin_clz(n) + 1;

        depths.resize(n);
        jumps.resize(n, std::vector<unsigned>(m));
        paths.resize(n, std::vector<Path>(m));

        prepare(tree, root, 0);

        for (unsigned i = 1; i < m; ++i) {
            for (unsigned u = 1; u < n; ++u) {
                const auto x = jumps[u][i-1];
                jumps[u][i] = jumps[x][i-1];
                paths[u][i] = Path(paths[u][i-1], paths[x][i-1]);
            }
        }
    }

    void prepare(const graph_t& tree, unsigned u, unsigned p)
    {
        jumps[u][0] = p;

        for (const auto& [v, d] : tree[u]) {
            if (v != p) {
                depths[v] = depths[u] + 1;
                paths[v][0] = Path(d);

                prepare(tree, v, u);
            }
        }
    }

    unsigned operator ()(unsigned u, unsigned v) const
    {
        const unsigned m = jumps[0].size();

        if (depths[v] < depths[u])
            std::swap(u, v);

        for (unsigned i = m-1; ~i != 0; --i) {
            if (depths[jumps[v][i]] >= depths[u])
                v = jumps[v][i];
        }

        if (v == u)
            return v;

        for (unsigned i = m-1; ~i != 0; --i) {
            if (jumps[v][i] != jumps[u][i]) {
                v = jumps[v][i];
                u = jumps[u][i];
            }
        }
        return jumps[v][0];
    }

    Path lift(unsigned u, unsigned lca) const
    {
        const auto m = jumps[0].size();

        Path p;
        for (unsigned i = 0, d = depths[u] - depths[lca]; i < m; ++i) {
            if ((d & 1 << i) != 0) {
                p = Path(p, paths[u][i]);
                u = jumps[u][i];
            }
        }
        return p;
    }
};

struct Query {
    unsigned r1;
    unsigned c1;
    unsigned r2;
    unsigned c2;
};

std::istream& operator >>(std::istream& input_stream, Query& query)
{
    return input_stream >> query.r1 >> query.c1 >> query.r2 >> query.c2;
}

void solve(const std::vector<std::string>& grid, const std::vector<Query>& rs)
{
    const size_t h = grid.size(), w = grid[0].size();

    graph_t tree(1);

    std::vector<std::vector<unsigned>> node_index(h, std::vector<unsigned>(w));
    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j) {
            if (grid[i][j] != '#')
                continue;

            const unsigned v = static_cast<unsigned>(tree.size());
            node_index[i][j] = v;
            tree.emplace_back();

            if (i != 0 && grid[i-1][j] == '#') {
                const unsigned u = node_index[i-1][j];
                tree[u].emplace_back(v, true);
                tree[v].emplace_back(u, true);
            }
            if (j != 0 && grid[i][j-1] == '#') {
                const unsigned u = node_index[i][j-1];
                tree[u].emplace_back(v, false);
                tree[v].emplace_back(u, false);
            }
        }
    }

    const LCA lca(tree, 1);

    for (const auto& q : rs) {
        const unsigned u = node_index[q.r1-1][q.c1-1], v = node_index[q.r2-1][q.c2-1], w = lca(u, v);
        const auto pu = lca.lift(u, w), pv = lca.lift(v, w);
        std::cout << Path(pu, pv.reverse()).turn_count << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t h, w;
    std::cin >> h >> w;

    std::vector<std::string> grid(h);
    for (size_t i = 0; i < h; ++i)
        std::cin >> grid[i];

    size_t q;
    std::cin >> q;

    std::vector<Query> rs(q);
    for (size_t i = 0; i < q; ++i)
        std::cin >> rs[i];

    solve(grid, rs);

    return 0;
}
