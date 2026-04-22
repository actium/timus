#include <iostream>
#include <vector>

struct Point {
    unsigned id;
    int x;
    int y;
};

unsigned distance(const Point& s, const Point& t)
{
    const auto dx = s.x - t.x, dy = s.y - t.y;
    return dx * dx + dy * dy;
}

void solve(std::vector<Point>& ps)
{
    std::vector<unsigned> t;
    while (!ps.empty()) {
        const auto p = ps.back();
        ps.pop_back();

        t.push_back(p.id);

        std::pair<unsigned, size_t> x = { 0, ps.size() };
        for (size_t i = 0; i < ps.size(); ++i)
            x = std::max(x, std::make_pair(distance(ps[i], p), i));

        if (x.second != ps.size())
            std::swap(ps[x.second], ps.back());
    }

    std::cout << "YES" << '\n';
    for (const auto x : t)
        std::cout << x << ' ';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Point> ps(1+n+1);
    for (size_t i = 0; i < n + 2; ++i) {
        ps[i].id = 1 + i;
        std::cin >> ps[i].x >> ps[i].y;
    }

    solve(ps);

    return 0;
}
