#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

void answer(unsigned u, unsigned v)
{
    std::cout << "YES" << '\n';
    std::cout << u << ' ' << v << '\n';
}

struct Point {
    int x;
    int y;
};

std::istream& operator >>(std::istream& input, Point& point)
{
    return input >> point.x >> point.y;
}

long long cross_product(const Point& o, const Point& s, const Point& t)
{
    const long long ldx = s.x - o.x, ldy = s.y - o.y;
    const long long rdx = t.x - o.x, rdy = t.y - o.y;
    return ldx * rdy - ldy * rdx;
}

bool on_segment(const Point& s, const Point& t, const Point& q)
{
    return q.x >= std::min(s.x, t.x) && q.x <= std::max(s.x, t.x)
        && q.y >= std::min(s.y, t.y) && q.y <= std::max(s.y, t.y);
}

struct Segment {
    unsigned id;
    Point s;
    Point t;
};

bool operator <(const Segment& lhs, const Segment& rhs)
{
    if (lhs.s.x == rhs.s.x)
        return lhs.s.y < rhs.s.y;

    return lhs.s.x < rhs.s.x ? cross_product(lhs.t, lhs.s, rhs.s) < 0 : cross_product(rhs.t, rhs.s, lhs.s) > 0;
}

bool check_intersection(const Segment& p, const Segment& q)
{
    const auto cp1 = cross_product(p.s, p.t, q.s), cp2 = cross_product(p.s, p.t, q.t);
    if (cp1 != 0 && cp2 != 0 && (cp1 < 0) == (cp2 < 0))
        return false;

    const auto cp3 = cross_product(q.s, q.t, p.s), cp4 = cross_product(q.s, q.t, p.t);
    if (cp3 != 0 && cp4 != 0 && (cp3 < 0) == (cp4 < 0))
        return false;

    if (cp1 != 0 || cp2 != 0 || cp3 != 0 || cp4 != 0)
        return true;

    return on_segment(p.s, p.t, q.s) || on_segment(p.s, p.t, q.t)
        || on_segment(q.s, q.t, p.s) || on_segment(q.s, q.t, p.t);
}

struct Event {
    int time;
    unsigned type;
    size_t index;
};

void solve(const std::vector<Segment>& segments)
{
    const size_t n = segments.size();

    std::vector<Event> events;
    for (size_t i = 0; i < n; ++i) {
        events.push_back({ segments[i].s.x, 0, i });
        events.push_back({ segments[i].t.x, 1, i });
    }

    std::sort(events.begin(), events.end(), [&](const Event& lhs, const Event& rhs) {
        if (lhs.time != rhs.time)
            return lhs.time < rhs.time;

        if (lhs.type != rhs.type)
            return lhs.type < rhs.type;

        return segments[lhs.index].s.y < segments[rhs.index].s.y;
    });

    std::set<Segment> active_segments;
    for (const auto& event : events) {
        const auto& segment = segments[event.index];

        if (event.type == 0) {
            const auto it = active_segments.lower_bound(segment);
            if (it != active_segments.begin()) {
                const auto jt = std::prev(it);
                if (check_intersection(*jt, segment))
                    return answer(jt->id, segment.id);
            }
            if (it != active_segments.end() && check_intersection(*it, segment))
                return answer(it->id, segment.id);

            active_segments.insert(segment);
        } else {
            const auto it = active_segments.find(segment);
            if (it != active_segments.begin()) {
                const auto p = std::prev(it), q = std::next(it);
                if (q != active_segments.end() && check_intersection(*p, *q))
                    return answer(p->id, q->id);
            }

            active_segments.erase(it);
        }
    }

    std::cout << "NO" << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Segment> segments(n);
    for (size_t i = 0; i < n; ++i) {
        auto& segment = segments[i];
        segment.id = 1 + i;
        std::cin >> segment.s >> segment.t;

        if (std::tie(segment.s.x, segment.s.y) > std::tie(segment.t.x, segment.t.y))
            std::swap(segment.s, segment.t);
    }

    solve(segments);

    return 0;
}
