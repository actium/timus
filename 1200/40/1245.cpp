#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include <cassert>

constexpr int oo = 10000000;

struct Circle {
    int x;
    int y;
    int r;
};

struct Event {
    int time;
    unsigned type;
    size_t index;
};

unsigned area(int lb_x, int ub_x, int lb_y, int ub_y)
{
    assert(lb_x <= ub_x && lb_y <= ub_y);
    return std::max(100, ub_x - lb_x) * std::max(100, ub_y - lb_y);
}

template <typename Selector>
unsigned solve(size_t n, Selector&& select)
{
    std::vector<Event> events;
    for (size_t i = 0; i < n; ++i) {
        const Circle c = select(i);
        events.push_back({ c.x - c.r, 1, i });
        events.push_back({ c.x + c.r, 0, i });
    }

    std::sort(events.begin(), events.end(), [](const Event& lhs, const Event& rhs) {
        return lhs.time != rhs.time ? lhs.time < rhs.time : lhs.type < rhs.type;
    });

    std::set<std::pair<int, size_t>> p;
    for (size_t i = 0; i < n; ++i) {
        const Circle c = select(i);
        p.emplace(c.y - c.r, i);
        p.emplace(c.y + c.r, i);
    }

    unsigned b = area(events.front().time, events.back().time, p.begin()->first, p.rbegin()->first);

    int lb_y = oo, ub_y = -oo;

    std::set<size_t> active;
    for (size_t i = 0; i < 2 * n - 1; ++i) {
        const auto& event = events[i];

        const Circle c = select(event.index);
        if (event.type == 1) {
            lb_y = std::min(lb_y, c.y - c.r);
            ub_y = std::max(ub_y, c.y + c.r);
            active.insert(event.index);
        } else {
            p.erase(std::make_pair(c.y - c.r, event.index));
            p.erase(std::make_pair(c.y + c.r, event.index));
            active.erase(event.index);

            if (active.empty()) {
                assert(events[i+1].type == 1);

                const auto a1 = area(events.front().time, event.time, lb_y, ub_y);
                const auto a2 = area(events[i+1].time, events.back().time, p.begin()->first, p.rbegin()->first);

                b = std::min(b, a1 + a2);
            }
        }
    }

    return b;
}

unsigned solve(const std::vector<Circle>& cs)
{
    const size_t n = cs.size();

    const auto c1 = solve(n, [&](size_t i) { return Circle { cs[i].x, cs[i].y, cs[i].r }; });
    const auto c2 = solve(n, [&](size_t i) { return Circle { cs[i].y, cs[i].x, cs[i].r }; });

    return std::min(c1, c2);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Circle> cs(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> cs[i].r >> cs[i].x >> cs[i].y;

    std::cout << solve(cs) << '\n';

    return 0;
}
