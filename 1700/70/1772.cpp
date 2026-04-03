#include <iostream>
#include <set>
#include <vector>

using integer = long long;

constexpr integer oo = 1000000000000;

class SegmentTree {
public:
    explicit SegmentTree(unsigned size)
        : size_(size)
        , data_(2 * size, oo)
    {}

    void update(unsigned index, integer value)
    {
        index += size_;
        data_[index] = value;

        while (index > 1) {
            const unsigned parent = index >> 1;
            data_[parent] = std::min(data_[index], data_[index^1]);
            index = parent;
        }
    }

    integer query(unsigned begin, unsigned end) const
    {
        integer v = oo;
        for (unsigned lb = size_ + begin, ub = size_ + end; lb < ub; lb >>= 1, ub >>= 1) {
            if ((lb & 1) != 0)
                v = std::min(v, data_[lb++]);

            if ((ub & 1) != 0)
                v = std::min(v, data_[--ub]);
        }
        return v;
    }

private:
    unsigned size_;

    std::vector<integer> data_;

}; // class SegmentTree

integer solve(unsigned n, unsigned s, const std::vector<std::pair<unsigned, unsigned>>& b)
{
    SegmentTree tl(1+n+1), tr(1+n+1);

    std::set<unsigned> active_set;

    const auto update = [&](unsigned x, integer w) {
        if (x < 1 || x > n || w >= oo)
            return;

        tl.update(x, w - x);
        tr.update(x, w + x);
        active_set.insert(x);
    };

    update(s, 0);

    for (const auto& [lb, rb] : b) {
        const unsigned lx = lb - 1, rx = rb + 1;

        integer lc = oo;
        if (lx >= 1)
            lc = std::min(tl.query(1, lx+1) + lx, tr.query(lx, n+1) - lx);

        integer rc = oo;
        if (rx <= n)
            rc = std::min(tl.query(1, rx+1) + rx, tr.query(rx, n+1) - rx);

        for (auto it = active_set.lower_bound(lb); it != active_set.end() && *it <= rb; it = active_set.erase(it)) {
            tl.update(*it, oo);
            tr.update(*it, oo);
        }

        update(lx, lc);
        update(rx, rc);
    }

    integer w = oo;
    for (const unsigned x : active_set)
        w = std::min(w, tl.query(x, x+1) + x);

    return w;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, s;
    std::cin >> n >> s;

    size_t k;
    std::cin >> k;

    std::vector<std::pair<unsigned, unsigned>> b(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> b[i].first >> b[i].second;

    std::cout << solve(n, s, b) << '\n';

    return 0;
}
