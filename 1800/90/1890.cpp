#include <iostream>
#include <vector>

using integer = long long;

struct Node {
    std::vector<size_t> s;
    integer v;
};

struct Order {
    char t;
    size_t x;
    integer y;
    integer z;
};

size_t decompose(const std::vector<Node>& nodes, size_t u, size_t x, std::vector<std::pair<size_t, size_t>>& segments)
{
    segments[u].first = x;
    segments[u].second = x + 1;

    for (const size_t v : nodes[u].s)
        segments[u].second = decompose(nodes, v, segments[u].second, segments);

    return segments[u].second;
}

class SegmentTree {
    struct Node {
        integer b = 0;
        integer d = 0;
    };

public:
    explicit SegmentTree(size_t size)
        : size_(1)
    {
        while (size_ < size)
            size_ *= 2;

        data_.resize(2 * size_);
    }

    void add(size_t lower_bound, size_t upper_bound, integer delta)
    {
        add(lower_bound, upper_bound, delta, 1, 0, size_);
    }

    integer sum(size_t lower_bound, size_t upper_bound) const
    {
        return sum(lower_bound, upper_bound, 1, 0, size_);
    }

private:
    void add(size_t lb, size_t ub, integer delta, size_t x, size_t lx, size_t rx)
    {
        if (rx <= lb || ub <= lx)
            return;

        if (lb <= lx && rx <= ub) {
            data_[x].b += delta * (rx - lx);
            data_[x].d += delta;
            return;
        }

        const size_t mx = (lx + rx) / 2;
        add(lb, ub, delta, x<<1|0, lx, mx);
        add(lb, ub, delta, x<<1|1, mx, rx);

        data_[x].b = data_[x<<1|0].b + data_[x<<1|1].b + data_[x].d * (rx - lx);
    }

    integer sum(size_t lb, size_t ub, size_t x, size_t lx, size_t rx) const
    {
        if (rx <= lb || ub <= lx)
            return 0;

        if (lb <= lx && rx <= ub)
            return data_[x].b;

        const size_t mx = (lx + rx) / 2;
        return sum(lb, ub, x<<1|0, lx, mx) + sum(lb, ub, x<<1|1, mx, rx)
            + data_[x].d * (std::min(rx, ub) - std::max(lb, lx));
    }

private:
    size_t size_;

    std::vector<Node> data_;

}; // class SegmentTree

void solve(const std::vector<Node>& nodes, const std::vector<Order>& orders)
{
    const size_t n = nodes.size();

    std::vector<std::pair<size_t, size_t>> segments(n);
    decompose(nodes, 0, 0, segments);

    SegmentTree st(n + 1);
    for (size_t i = 0; i < n; ++i)
        st.add(segments[i].first, segments[i].first + 1, nodes[i].v);

    for (const Order& q : orders) {
        if (q.t == 'e') {
            const integer s = st.sum(segments[q.x].first, segments[q.x].first + 1);
            if (s < q.y)
                st.add(segments[q.x].first, segments[q.x].first + 1, q.z);
        } else {
            const integer s = st.sum(segments[q.x].first, segments[q.x].second);
            if (s < q.y * (segments[q.x].second - segments[q.x].first))
                st.add(segments[q.x].first, segments[q.x].second, q.z);
        }
    }

    for (size_t i = 0; i < n; ++i)
        std::cout << st.sum(segments[i].first, segments[i].first + 1) << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, q;
    std::cin >> n >> q;

    std::vector<Node> nodes(n);
    std::cin >> nodes[0].v;

    for (size_t i = 1; i < n; ++i) {
        size_t p;
        std::cin >> p;

        nodes[p].s.push_back(i);

        std::cin >> nodes[i].v;
    }

    std::vector<Order> orders(q);
    for (size_t i = 0; i < q; ++i) {
        std::string t;
        std::cin >> t;

        orders[i].t = t[0];

        std::cin >> orders[i].x >> orders[i].y >> orders[i].z;
    }

    solve(nodes, orders);

    return 0;
}
