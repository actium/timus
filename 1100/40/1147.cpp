#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Point {
    unsigned x;
    unsigned y;
};

std::istream& operator >>(std::istream& input, Point& point)
{
    return input >> point.x >> point.y;
}

struct Rectangle {
    Point lb;
    Point ub;
    unsigned color;
};

std::istream& operator >>(std::istream& input, Rectangle& rectangle)
{
    return input >> rectangle.lb >> rectangle.ub >> rectangle.color;
}

struct Event {
    int type;
    unsigned coordinate;
    size_t rectangle_id;
};

bool operator <(const Event& lhs, const Event& rhs)
{
    if (lhs.coordinate != rhs.coordinate)
        return lhs.coordinate < rhs.coordinate;

    if (lhs.type != rhs.type)
        return lhs.type < rhs.type;

    return lhs.rectangle_id < rhs.rectangle_id;
}

template <typename F>
unsigned process(bool pre, std::vector<Event>& events, F&& f)
{
    std::sort(events.begin(), events.end());

    unsigned scanline = 0;
    {
        std::set<size_t> active_rectangles;

        const auto update = [&active_rectangles](const Event& event) {
            if (event.type == +1) {
                active_rectangles.insert(event.rectangle_id);
            } else {
                active_rectangles.erase(event.rectangle_id);
            }
        };

        for (const Event& e : events) {
            if (pre) {
                update(e);
            }
            f(active_rectangles, e.coordinate - scanline);
            if (!pre) {
                update(e);
            }

            scanline = e.coordinate;
        }
    }
    return scanline;
}

std::vector<unsigned> solve(unsigned a, unsigned b, const std::vector<Rectangle>& rectangles)
{
    std::vector<unsigned> areas(1 + 2500);
    {
        std::vector<Event> events;
        for (size_t i = 0; i < rectangles.size(); ++i) {
            events.push_back({+1, rectangles[i].lb.x, i});
            events.push_back({-1, rectangles[i].ub.x, i});
        }

        unsigned color = 1;

        unsigned x = process(false, events, [&](const std::set<size_t>& ar, unsigned width) {
            std::vector<Event> events;
            for (const size_t rectangle_id : ar) {
                events.push_back({+1, rectangles[rectangle_id].lb.y, rectangle_id});
                events.push_back({-1, rectangles[rectangle_id].ub.y, rectangle_id});
            }

            unsigned y = process(true, events, [&](const std::set<size_t>& ar, unsigned height) {
                areas[color] += width * height;
                color = ar.empty() ? 1 : rectangles[*ar.rbegin()].color;
            });

            areas[color] += width * (b - y);
        });

        areas[color] += (a - x) * b;
    }
    return areas;
}

std::ostream& operator <<(std::ostream& output, const std::vector<unsigned>& areas)
{
    for (unsigned i = 1; i <= 2500; ++i) {
        if (areas[i] != 0) {
            output << i << ' ' << areas[i] << '\n';
        }
    }
    return output;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned a, b, n;
    std::cin >> a >> b >> n;

    std::vector<Rectangle> rectangles(n);
    for (Rectangle& r : rectangles) {
        std::cin >> r;
    }

    std::cout << solve(a, b, rectangles) << '\n';

    return 0;
}
