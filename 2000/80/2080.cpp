#include <algorithm>
#include <iostream>
#include <vector>

class MergeSortTree {
public:
    explicit MergeSortTree(const std::vector<size_t>& next)
        : size_(1)
    {
        while (size_ < next.size())
            size_ *= 2;

        data_.resize(2 * size_);
        build(next, 1, 0, size_);
    }

    unsigned query(size_t lb, size_t ub) const
    {
        return query(lb, ub, 1, 0, size_);
    }

private:
    unsigned query(size_t lb, size_t ub, size_t x, size_t lx, size_t rx) const
    {
        if (rx <= lb || ub <= lx)
            return 0;

        if (lb <= lx && rx <= ub)
            return data_[x].end() - std::lower_bound(data_[x].begin(), data_[x].end(), ub);

        const size_t mx = (lx + rx) / 2;
        return query(lb, ub, x<<1|0, lx, mx) + query(lb, ub, x<<1|1, mx, rx);
    }

    void build(const std::vector<size_t>& next, size_t x, size_t lx, size_t rx)
    {
        if (lx + 1 == rx) {
            data_[x].push_back(lx < next.size() ? next[lx] : size_);
        } else {
            const size_t mx = (lx + rx) / 2;
            build(next, x<<1|0, lx, mx);
            build(next, x<<1|1, mx, rx);
            merge(x);
        }
    }

    void merge(size_t x)
    {
        const size_t sz1 = data_[x<<1|0].size(), sz2 = data_[x<<1|1].size();

        size_t i = 0, j = 0;
        while (i < sz1 && j < sz2) {
            if (data_[x<<1|0][i] > data_[x<<1|1][j]) {
                data_[x].push_back(data_[x<<1|1][j++]);
            } else {
                data_[x].push_back(data_[x<<1|0][i++]);
            }
        }

        while (i < sz1)
            data_[x].push_back(data_[x<<1|0][i++]);

        while (j < sz2)
            data_[x].push_back(data_[x<<1|1][j++]);
    }

private:
    size_t size_;

    std::vector<std::vector<unsigned>> data_;

}; // class MergeSortTree

void solve(size_t n, const std::vector<unsigned>& a)
{
    const size_t k = a.size();

    std::vector<bool> v(n);
    for (const unsigned x : a) {
        if (!v[x-1]) {
            std::cout << x << ' ';
            v[x-1] = true;
        }
    }
    for (size_t i = 0; i < n; ++i) {
        if (!v[i])
            std::cout << 1 + i << ' ';
    }
    std::cout << '\n';

    std::vector<size_t> next(k);
    {
        std::vector<size_t> x(n, k);
        for (size_t i = k; i-- > 0; ) {
            next[i] = x[a[i]-1];
            x[a[i]-1] = i;
        }
    }

    const MergeSortTree mst(next);
    for (size_t i = 0; i < k; ++i)
        std::cout << mst.query(i, next[i]) - 1 << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, k;
    std::cin >> n >> k;

    std::vector<unsigned> a(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> a[i];

    solve(n, a);

    return 0;
}
