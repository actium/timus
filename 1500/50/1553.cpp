#include <iostream>
#include <vector>

struct Query {
    char type;
    unsigned u;
    unsigned v;
};

std::istream& operator >>(std::istream& input, Query& query)
{
    return input >> query.type >> query.u >> query.v;
}

class Tree {
public:
    explicit Tree(unsigned vertex_count)
        : vertex_count_(vertex_count)
        , adjacents_(vertex_count)
        , subtree_sizes_(vertex_count)
        , parents_(vertex_count)
    {}

    unsigned get_vertex_count() const
    {
        return vertex_count_;
    }

    unsigned get_parent(unsigned vertex) const
    {
        return parents_[vertex];
    }

    void add_edge(unsigned u, unsigned v)
    {
        adjacents_[u].push_back(v);
        adjacents_[v].push_back(u);
    }

    std::vector<std::vector<unsigned>> decompose()
    {
        const unsigned root = 0;

        traverse(root, root);

        std::vector<std::vector<unsigned>> paths(1);
        if (vertex_count_ > 1)
            decompose(root, root, paths);
        else
            paths[0].push_back(root);

        return paths;
    }

private:
    void traverse(unsigned vertex, unsigned parent)
    {
        subtree_sizes_[vertex] = 1;
        parents_[vertex] = parent;

        for (const unsigned v : adjacents_[vertex]) {
            if (v != parent) {
                traverse(v, vertex);
                subtree_sizes_[vertex] += subtree_sizes_[v];
            }
        }
    }

    void decompose(unsigned vertex, unsigned parent, std::vector<std::vector<unsigned>>& paths)
    {
        paths.back().push_back(vertex);

        if (adjacents_[vertex].size() == 1 && adjacents_[vertex][0] == parent)
            return;

        const unsigned heaviest_subtree_root = select_heaviest_subtree(vertex, parent);
        decompose(heaviest_subtree_root, vertex, paths);

        for (const unsigned v : adjacents_[vertex]) {
            if (v != parent && v != heaviest_subtree_root) {
                paths.emplace_back();
                decompose(v, vertex, paths);
            }
        }
    }

    unsigned select_heaviest_subtree(unsigned vertex, unsigned parent) const
    {
        unsigned subtree_root = vertex_count_;
        for (const unsigned v : adjacents_[vertex]) {
            if (v == parent)
                continue;

            if (subtree_root == vertex_count_ || subtree_sizes_[v] > subtree_sizes_[subtree_root])
                subtree_root = v;
        }
        return subtree_root;
    }

private:
    const unsigned vertex_count_;

    std::vector<std::vector<unsigned>> adjacents_;

    std::vector<unsigned> subtree_sizes_;
    std::vector<unsigned> parents_;

}; // class Tree

class SegmentTree {
public:
    explicit SegmentTree(size_t size)
        : size_(size)
        , data_(2 * size)
    {}

    void update(size_t index, unsigned delta)
    {
        index += size_;
        data_[index] += delta;

        while (index > 1) {
            const size_t parent = index >> 1;
            data_[parent] = std::max(data_[index], data_[index ^ 1]);
            index = parent;
        }
    }

    unsigned reduce(size_t left_index, size_t right_index) const
    {
        if (left_index > right_index)
            std::swap(left_index, right_index);

        size_t lb = size_ + left_index;
        unsigned left = data_[lb++];

        size_t ub = size_ + right_index + 1;
        unsigned right = data_[--ub];

        while (lb < ub) {
            if (lb & 1)
                left = std::max(left, data_[lb++]);

            if (ub & 1)
                right = std::max(right, data_[--ub]);

            lb >>= 1, ub >>= 1;
        }

        return std::max(left, right);
    }

private:
    const size_t size_;

    std::vector<unsigned> data_;

}; // class SegmentTree

void solve(Tree& tree, const std::vector<Query>& queries)
{
    const unsigned vertex_count = tree.get_vertex_count();

    const std::vector<std::vector<unsigned>> paths = tree.decompose();

    std::vector<unsigned> path_indices(vertex_count);
    std::vector<unsigned> segment_tree_indices(vertex_count);

    unsigned next_segment_tree_index = 0;
    for (size_t i = 0; i < paths.size(); ++i) {
        const std::vector<unsigned>& path = paths[i];

        for (size_t j = 0; j < path.size(); ++j) {
            const unsigned vertex = path[j];

            path_indices[vertex] = i;
            segment_tree_indices[vertex] = next_segment_tree_index++;
        }
    }

    SegmentTree st(vertex_count);

    const auto query = [&](unsigned u, unsigned v) {
        unsigned x = 0;
        while (path_indices[u] != path_indices[v]) {
            if (path_indices[u] < path_indices[v])
                std::swap(u, v);

            const unsigned p = paths[path_indices[u]].front();
            x = std::max(x, st.reduce(segment_tree_indices[u], segment_tree_indices[p]));

            u = tree.get_parent(p);
        }
        return std::max(x, st.reduce(segment_tree_indices[u], segment_tree_indices[v]));
    };

    for (const Query& q : queries) {
        if (q.type == 'I') {
            const unsigned vertex_index = segment_tree_indices[q.u - 1];
            st.update(vertex_index, q.v);
        } else {
            std::cout << query(q.u - 1, q.v - 1) << '\n';
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    Tree tree(n);
    for (size_t i = 1; i < n; ++i) {
        unsigned a, b;
        std::cin >> a >> b;

        tree.add_edge(a - 1, b - 1);
    }

    size_t q;
    std::cin >> q;

    std::vector<Query> queries(q);
    for (size_t i = 0; i < q; ++i)
        std::cin >> queries[i];

    solve(tree, queries);

    return 0;
}
