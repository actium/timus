#include <iostream>
#include <utility>
#include <vector>

using point_t = std::pair<int, int>;
using segment_t = std::pair<unsigned, unsigned>;

class ComponentSet {
public:
    explicit ComponentSet(unsigned size)
        : size_(size)
        , roots_(size)
        , ranks_(size)
    {
        for (unsigned i = 0; i < size; ++i)
            roots_[i] = i;
    }

    unsigned size() const
    {
        return size_;
    }

    void merge(unsigned u, unsigned v)
    {
        unsigned ru = resolve(u), rv = resolve(v);
        if (ru == rv)
            return;

        if (ranks_[ru] < ranks_[rv])
            std::swap(ru, rv);

        roots_[rv] = ru;

        if (ranks_[ru] == ranks_[rv])
            ++ranks_[ru];

        --size_;
    }

private:
    unsigned resolve(unsigned x)
    {
        while (x != roots_[x])
            x = std::exchange(roots_[x], roots_[roots_[x]]);

        return x;
    }

private:
    unsigned size_;

    std::vector<unsigned> roots_;
    std::vector<unsigned> ranks_;

}; // class ComponentSet

int cross_product(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
    return a.first * b.second - a.second * b.first;
}

bool check(const point_t u[2], const point_t v[2])
{
    const std::pair<int, int> s1 = { u[1].first - u[0].first, u[1].second - u[0].second };
    const std::pair<int, int> s2 = { v[1].first - v[0].first, v[1].second - v[0].second };

    const int p1 = cross_product(s1, { v[0].first - u[0].first, v[0].second - u[0].second });
    const int p2 = cross_product(s1, { v[1].first - u[0].first, v[1].second - u[0].second });

    if ((p1 < 0) == (p2 < 0) || p1 == 0 || p2 == 0)
        return false;

    const int p3 = cross_product(s2, { u[0].first - v[0].first, u[0].second - v[0].second });
    const int p4 = cross_product(s2, { u[1].first - v[0].first, u[1].second - v[0].second });

    if ((p3 < 0) == (p4 < 0) || p3 == 0 || p4 == 0)
        return false;

    return true;
}

bool check(const point_t u[2], const point_t& v)
{
    const std::pair<int, int> s = { u[1].first - u[0].first, u[1].second - u[0].second };

    return cross_product(s, { v.first - u[0].first, v.second - u[0].second }) == 0
        && v.first >= std::min(u[0].first, u[1].first)
        && v.first <= std::max(u[0].first, u[1].first)
        && v.second >= std::min(u[0].second, u[1].second)
        && v.second <= std::max(u[0].second, u[1].second);
}

bool solve(const std::vector<point_t>& p, const std::vector<segment_t>& s)
{
    const size_t n = p.size(), m = s.size();

    ComponentSet cs(n);
    for (size_t i = 0; i < m; ++i) {
        cs.merge(s[i].first - 1, s[i].second - 1);

        const point_t u[2] = { p[s[i].first-1], p[s[i].second-1] };
        for (size_t j = 0; j < i; ++j) {
            const point_t v[2] = { p[s[j].first-1], p[s[j].second-1] };
            if (check(u, v))
                cs.merge(s[i].first-1, s[j].first-1);
        }

        for (size_t j = 0; j < n; ++j) {
            if (check(u, p[j]))
                cs.merge(s[i].first-1, j);
        }
    }

    return cs.size() == 1;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<point_t> p(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> p[i].first >> p[i].second;

    std::vector<segment_t> s(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> s[i].first >> s[i].second;

    std::cout << (solve(p, s) ? "YES" : "NO") << '\n';

    return 0;
}
