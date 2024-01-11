#include <iostream>
#include <utility>
#include <vector>

constexpr unsigned M = 1000000007;

class DisjointSetUnion {
public:
    explicit DisjointSetUnion(unsigned size)
        : size_(size)
        , data_(size, -1)
    {}

    unsigned size() const noexcept
    {
        return size_;
    }

    unsigned size(unsigned x) noexcept
    {
        return -data_[locate(x)];
    }

    unsigned locate(unsigned x) noexcept
    {
        unsigned rx = x;
        while (data_[rx] >= 0)
            rx = data_[rx];

        while (data_[x] >= 0)
            x = std::exchange(data_[x], rx);

        return rx;
    }

    bool unite(unsigned u, unsigned v)
    {
        unsigned ru = locate(u), rv = locate(v);
        if (ru == rv)
            return false;

        if (data_[ru] > data_[rv])
            std::swap(ru, rv);

        data_[ru] += data_[rv];
        data_[rv] = ru;
        --size_;

        return true;
    }

private:
    unsigned size_;

    std::vector<int> data_;

}; // class DisjointSetUnion

unsigned solve(size_t n, const std::vector<unsigned>& k)
{
    const size_t m = k.size();

    if (n == 2)
        return 1;

    std::vector<unsigned> d(n);
    for (size_t i = 0; i < m; ++i) {
        if (++d[k[i]-1] == 3)
            return 0;
    }

    DisjointSetUnion dsu(n);
    for (size_t i = 0; i < m; ++i) {
        if (!dsu.unite(i, k[i]-1) && dsu.size() != 1 && k[k[i]-1] != i+1)
            return 0;
    }

    std::vector<unsigned> sizes(n);
    for (size_t i = 0; i < n; ++i)
        sizes[dsu.locate(i)] = dsu.size(i);

    unsigned long long q = 1;
    for (const unsigned x : sizes) {
        if (x > 1)
            q = q * 2 % M;
    }
    for (unsigned i = dsu.size() - 1; i > 1; --i)
        q = q * i % M;

    return q;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<unsigned> k(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> k[i];

    std::cout << solve(n, k) << '\n';

    return 0;
}
