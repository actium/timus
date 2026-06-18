#include <iostream>
#include <vector>

using integer = unsigned long long;

constexpr integer oo = ~integer(0) >> 1;

struct SegmentTree {
    size_t size;
    std::vector<integer> nodes;

    explicit SegmentTree(size_t n)
        : size(1)
    {
        while (size < n)
            size *= 2;

        nodes.resize(2 * size, oo);
    }

    void update(size_t index, integer value)
    {
        index += size;
        nodes[index] = value;

        for (index >>= 1; index != 0; index >>= 1)
            nodes[index] = std::min(nodes[index<<1|0], nodes[index<<1|1]);
    }

    integer query(size_t begin, size_t end) const
    {
        integer v = oo;
        for (begin += size, end += size; begin < end; begin >>= 1, end >>= 1) {
            if ((begin & 1) != 0)
                v = std::min(v, nodes[begin++]);
            if ((end & 1) != 0)
                v = std::min(v, nodes[--end]);
        }
        return v;
    }
};

struct Pointer {
    size_t lx = 0;
    size_t rx = 0;

    __int128_t product = 1;
};

int solve(const std::vector<unsigned>& cs, integer lb, integer ub)
{
    const size_t n = cs.size();

    std::vector<std::pair<size_t, size_t>> r(n);
    {
        Pointer lp, rp;
        for (size_t i = 0; i < n; ++i) {
            while (lp.lx < i)
                lp.product /= cs[lp.lx++];
            while (lp.rx < n && (lp.rx == i || lp.product < lb))
                lp.product *= cs[lp.rx++];

            while (rp.lx < i)
                rp.product /= cs[rp.lx++];
            while (rp.rx < n && rp.product <= ub)
                rp.product *= cs[rp.rx++];

            r[i].first = lp.rx + (lp.product < lb);
            r[i].second = rp.rx + (rp.product <= ub);
        }
    }

    SegmentTree st(n+1);
    st.update(n, 0);

    std::vector<integer> dp(n, oo);
    for (size_t i = n-1; ~i != 0; --i) {
        dp[i] = 1 + st.query(r[i].first, r[i].second);
        st.update(i, dp[i]);
    }
    return dp[0] < oo ? static_cast<int>(dp[0]) : -1;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    integer lb, ub;
    std::cin >> lb >> ub;

    std::vector<unsigned> cs(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> cs[i];

    std::cout << solve(cs, lb, ub) << '\n';

    return 0;
}
