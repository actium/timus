#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

class DisjointSetUnion {
public:
    explicit DisjointSetUnion(unsigned size)
        : data_(size, -1)
    {}

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

    void unite(unsigned u, unsigned v)
    {
        unsigned ru = locate(u), rv = locate(v);
        if (ru == rv)
            return;

        if (data_[ru] > data_[rv])
            std::swap(ru, rv);

        data_[ru] += data_[rv];
        data_[rv] = ru;
    }

private:
    std::vector<int> data_;

}; // class DisjointSetUnion

struct Point {
    int x;
    int y;
};

std::istream& operator >>(std::istream& input_stream, Point& point)
{
    return input_stream >> point.x >> point.y;
}

struct Rectangle {
    Point corners[2];

    unsigned width() const
    {
        return corners[1].x - corners[0].x;
    }

    unsigned height() const
    {
        return corners[1].y - corners[0].y;
    }

    bool contains(const Point& p) const
    {
        return corners[0].x <= p.x && p.x < corners[1].x
            && corners[0].y <= p.y && p.y < corners[1].y;
    }
};

template <typename Selector>
void process(const std::vector<Rectangle>& bs, DisjointSetUnion& dsu, Selector&& select)
{
    const size_t n = bs.size();

    std::map<int, std::vector<size_t>> oe, ce;
    for (size_t i = 0; i < n; ++i) {
        const auto ls = select(bs[i].corners[0]), rs = select(bs[i].corners[1]);
        oe[ls.x].push_back(i);
        ce[rs.x].push_back(i);
    }

    const auto sort = [&](std::map<int, std::vector<size_t>>& es) {
        for (auto& e : es) {
            std::sort(e.second.begin(), e.second.end(), [&](size_t i, size_t j) {
                const auto ls = select(bs[i].corners[0]), rs = select(bs[j].corners[0]);
                return ls.y < rs.y;
            });
        }
    };

    sort(oe);
    sort(ce);

    for (auto& e : ce) {
        const auto rs = oe.find(e.first + 1);
        if (rs == oe.end())
            continue;

        auto it = e.second.begin(), jt = rs->second.begin();
        while (it != e.second.end() && jt != rs->second.end()) {
            const Rectangle lhs = { select(bs[*it].corners[0]), select(bs[*it].corners[1]) };
            const Rectangle rhs = { select(bs[*jt].corners[0]), select(bs[*jt].corners[1]) };

            if (lhs.corners[1].y < rhs.corners[0].y) {
                ++it;
                continue;
            }
            if (rhs.corners[1].y < lhs.corners[0].y) {
                ++jt;
                continue;
            }

            dsu.unite(*it, *jt);

            if (lhs.corners[1].y <= rhs.corners[1].y)
                ++it;
            if (rhs.corners[1].y <= lhs.corners[1].y)
                ++jt;
        }
    }
}

unsigned solve(const std::vector<Rectangle>& bs, const Point& s)
{
    const size_t n = bs.size();

    size_t p = 0;
    while (!bs[p].contains(s))
        ++p;

    if (bs[p].width() == 3 && bs[p].height() == 3 && s.x == bs[p].corners[0].x + 1 && s.y == bs[p].corners[0].y + 1)
        return 1;

    DisjointSetUnion dsu(n);
    process(bs, dsu, [](const Point& corner) { return Point { corner.x, corner.y }; });
    process(bs, dsu, [](const Point& corner) { return Point { corner.y, corner.x }; });
    return dsu.size(p);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    unsigned m;
    std::cin >> m;

    Point s;
    std::cin >> s;

    std::vector<Rectangle> bs(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> bs[i].corners[0] >> bs[i].corners[1];

    std::cout << solve(bs, s) << '\n';

    return 0;
}
