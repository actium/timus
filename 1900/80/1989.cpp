#include <iostream>
#include <vector>

using integer = unsigned long long;

constexpr unsigned N = 100000;
constexpr unsigned P = 31;

integer powers[1+N] = { 1 };

void initialize(size_t n)
{
    for (size_t i = 1; i <= n; ++i)
        powers[i] = powers[i-1] * P;
}

class SegmentTree {
public:
    template <typename Iterator>
    SegmentTree(Iterator begin, Iterator end)
        : length_(std::distance(begin, end))
        , size_(1)
    {
        while (size_ < length_)
            size_ *= 2;

        nodes_.resize(2 * size_);

        std::vector<integer> h(1 + length_);
        for (size_t i = 0; i < length_; ++i, ++begin)
            h[i+1] = *begin * powers[i];

        build(h, 1, 1, length_);
    }

    void update(size_t index, integer v)
    {
        update(index, v, 1, 1, length_);
    }

    integer query(size_t lb, size_t ub) const
    {
        return query(lb, ub, 1, 1, length_);
    }

private:
    void build(const std::vector<integer>& h, size_t x, size_t lx, size_t rx)
    {
        if (lx == rx) {
            nodes_[x] = h[lx];
            return;
        }

        const size_t mx = (lx + rx) / 2;
        build(h, x<<1|0, lx, mx);
        build(h, x<<1|1, mx + 1, rx);

        combine(x);
    }

    void combine(size_t x)
    {
        nodes_[x] = nodes_[x<<1|0] + nodes_[x<<1|1];
    }

    void update(size_t index, integer v, size_t x, size_t lx, size_t rx)
    {
        if (lx == rx) {
            nodes_[x] = v;
            return;
        }

        const size_t mx = (lx + rx) / 2;
        if (index <= mx)
            update(index, v, x<<1|0, lx, mx);
        else
            update(index, v, x<<1|1, mx + 1, rx);

        combine(x);
    }

    integer query(size_t lb, size_t ub, size_t x, size_t lx, size_t rx) const
    {
        if (lb <= lx && rx <= ub)
            return nodes_[x];

        const size_t mx = (lx + rx) / 2;

        integer v = 0;
        if (lb <= mx)
            v += query(lb, ub, x<<1|0, lx, mx);
        if (ub > mx)
            v += query(lb, ub, x<<1|1, mx + 1, rx);

        return v;
    }

private:
    const size_t length_;

    size_t size_;

    std::vector<integer> nodes_;

}; // class SegmentTree

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    const size_t n = s.length();

    initialize(n);

    size_t m;
    std::cin >> m;

    SegmentTree st(s.begin(), s.end()), tt(s.rbegin(), s.rend());
    for (size_t i = 0; i < m; ++i) {
        std::string type;
        std::cin >> type;

        if (type == "change") {
            unsigned x;
            char c;
            std::cin >> x >> c;

            st.update(x, c * powers[x - 1]);
            tt.update(n + 1 - x, c * powers[n - x]);
        } else {
            unsigned i, j;
            std::cin >> i >> j;

            const unsigned ri = n + 1 - j, rj = n + 1 - i;

            integer h1 = st.query(i, j);
            integer h2 = tt.query(ri, rj);
            if (ri > i)
                h1 *= powers[ri - i];
            else
                h2 *= powers[i - ri];

            std::cout << (h1 == h2 ? "Yes" : "No") << '\n';
        }
    }

    return 0;
}
