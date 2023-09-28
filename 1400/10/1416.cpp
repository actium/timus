#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
    unsigned a;
    unsigned b;
    unsigned w;
};

class ComponentSet {
public:
    explicit ComponentSet(unsigned size)
        : size_(size), roots_(size), ranks_(size)
    {
        for (unsigned i = 0; i < size; ++i)
            roots_[i] = i;
    }

    unsigned size() const
    {
        return size_;
    }

    unsigned lookup(unsigned x)
    {
        while (x != roots_[x]) {
            const unsigned t = roots_[x];
            roots_[x] = roots_[t];
            x = t;
        }
        return x;
    }

    template <typename F>
    void merge(unsigned u, unsigned v, F&& postprocess)
    {
        unsigned ru = lookup(u), rv = lookup(v);
        if (ru == rv)
            return;

        if (ranks_[ru] < ranks_[rv])
            std::swap(ru, rv);

        roots_[rv] = ru;

        if (ranks_[ru] == ranks_[rv])
            ++ranks_[ru];

        --size_;

        postprocess(ru, rv);
    }

private:
    unsigned size_;

    std::vector<unsigned> roots_;
    std::vector<unsigned> ranks_;

}; // class ComponentSet

void solve(size_t n, const std::vector<Edge>& e)
{
    const size_t m = e.size();

    std::vector<unsigned> s;
    {
        unsigned w = 0;

        ComponentSet cs(n);
        for (size_t i = 0; i < m; ++i) {
            cs.merge(e[i].a - 1, e[i].b - 1, [&](unsigned, unsigned) {
                w += e[i].w;
                s.push_back(i);
            });
        }

        std::cout << "Cost: " << w << '\n';
    }

    unsigned v = ~0u;
    for (const size_t x : s) {
        unsigned w = 0;

        ComponentSet cs(n);
        for (size_t i = 0; i < m; ++i) {
            if (i != x)
                cs.merge(e[i].a - 1, e[i].b - 1, [&](unsigned, unsigned) {
                    w += e[i].w;
                });
        }

        if (cs.size() == 1 && w < v)
            v = w;
    }

    std::cout << "Cost: " << static_cast<int>(v) << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<Edge> e(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> e[i].a >> e[i].b >> e[i].w;

    std::sort(e.begin(), e.end(), [](const Edge& lhs, const Edge& rhs) {
        return lhs.w < rhs.w;
    });

    solve(n, e);

    return 0;
}
