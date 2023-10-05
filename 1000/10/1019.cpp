#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Segment {
    unsigned a;
    unsigned b;
    char c;
};

struct Event {
    int t;
    unsigned x;
    size_t s;
};

bool operator <(const Event& lhs, const Event& rhs)
{
    if (lhs.x != rhs.x)
        return lhs.x < rhs.x;

    if (lhs.t != rhs.t)
        return lhs.t < rhs.t;

    return lhs.s < rhs.s;
}

void solve(const std::vector<Segment>& segments)
{
    std::vector<Event> events;
    for (size_t i = 0; i < segments.size(); ++i) {
        if (segments[i].a < segments[i].b) {
            events.push_back({ +1, segments[i].a, i });
            events.push_back({ -1, segments[i].b, i });
        }
    }

    std::sort(events.begin(), events.end());

    std::vector<std::pair<unsigned, unsigned>> w;
    w.emplace_back(0, 0);

    std::set<size_t> s;
    unsigned x = 0;
    for (const Event& e : events) {
        if (s.empty() || segments[*s.rbegin()].c == 'w')
            w.emplace_back(x, e.x);

        if (e.t == 1)
            s.insert(e.s);
        else
            s.erase(e.s);

        x = e.x;
    }

    std::pair<unsigned, unsigned> r = {};
    for (size_t i = 1; i < w.size(); ++i) {
        if (w[i].first == w[0].second)
            w[0].second = w[i].second;
        else
            w[0] = w[i];

        if (w[0].second - w[0].first > r.second - r.first)
            r = w[0];
    }

    std::cout << r.first << ' ' << r.second << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Segment> segments(1 + n);
    segments[0] = { 0, 1000000000, 'w' };
    for (size_t i = 1; i <= n; ++i)
        std::cin >> segments[i].a >> segments[i].b >> segments[i].c;


    solve(segments);

    return 0;
}
