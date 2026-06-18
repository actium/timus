#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

class DisjointSetUnion {
public:
    explicit DisjointSetUnion(unsigned size)
        : data_(size, -1)
    {}

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
        return true;
    }

private:
    std::vector<int> data_;

}; // class DisjointSetUnion

struct Port {
    unsigned u;
    unsigned v;
    unsigned d;
    unsigned c;
};

double evaluate(size_t n, std::vector<Port>& ps, double x)
{
    unsigned long long d = 0, c = 0;

    std::sort(ps.begin(), ps.end(), [&](const Port& lhs, const Port& rhs) {
        return lhs.c - x * lhs.d < rhs.c - x * rhs.d;
    });

    DisjointSetUnion dsu(1+n);
    for (const auto& p : ps) {
        if (dsu.unite(p.u, p.v)) {
            d += p.d;
            c += p.c;
        }
    }

    return static_cast<double>(c) / d;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cout.precision(8);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<Port> ps(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> ps[i].u >> ps[i].v >> ps[i].d >> ps[i].c;

    double x = 0, y = evaluate(n, ps, x);
    while (std::abs(x - y) > 1e-8)
        x = std::exchange(y, evaluate(n, ps, y));

    std::cout << std::fixed << x << '\n';

    return 0;
}
