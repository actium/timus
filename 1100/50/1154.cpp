#include <algorithm>
#include <string>
#include <vector>

#include <cstdio>

struct Point {
    int x;
    int y;
};

struct Segment {
    Point s;
    Point t;
    int x;
};

long double evaluate(const std::vector<Segment>& segments, int x)
{
    long double value = 0;
    for (const auto& segment : segments) {
        if (segment.s.x <= x && x < segment.t.x) {
            const auto dx = segment.t.x - segment.s.x, dy = segment.t.y - segment.s.y;
            const auto dv = static_cast<long double>(x - segment.s.x) * dy / dx;
            value += segment.x * (segment.s.y + dv);
        }
    }
    return value;
}

unsigned read_timestamp()
{
    unsigned h, m, s;
    scanf("%02u:%02u:%02u", &h, &m, &s);

    return (h * 60 + m) * 60 + s;
}

void write_timestamp(unsigned t)
{
    const unsigned h = t / 3600;
    const unsigned m = t % 3600 / 60;
    const unsigned s = t % 60;

    printf("%02u:%02u:%02u", h, m, s);
}

struct Info {
    char id;
    Point moments[2];
};

void solve(const Info (& infos)[4], const std::string& s, const std::string& t)
{
    int b[26] = {};
    for (const char c : s)
        ++b[c-'A'];
    for (const char c : t)
        --b[c-'A'];

    std::vector<Segment> segments;
    std::vector<unsigned> timestamps;
    for (const auto& info : infos) {
        const int x = b[info.id-'A'];
        if (x == 0)
            continue;

        const Point p0 = { info.moments[1].x - 86400, info.moments[1].y };
        const Point p1 = info.moments[0];
        const Point p2 = info.moments[1];
        const Point p3 = { info.moments[0].x + 86400, info.moments[0].y };

        segments.push_back({ p0, p1, x });
        segments.push_back({ p1, p2, x });
        segments.push_back({ p2, p3, x });

        timestamps.push_back(info.moments[0].x);
        timestamps.push_back(info.moments[1].x);
    }

    std::sort(timestamps.begin(), timestamps.end());

    std::pair<long double, unsigned> best = { evaluate(segments, 0), 0 };
    for (const auto ts : timestamps) {
        const auto value = evaluate(segments, ts);
        if (value > best.first + 1e-9)
            best = { value, ts };
    }

    if (best.first > 0) {
        write_timestamp(best.second);
        printf("\n%.02Lf\n", best.first);
    } else {
        printf("We can't win!\n");
    }
}

int main()
{
    Info infos[4];
    for (auto& info : infos) {
        scanf("%c ", &info.id);

        info.moments[0].x = read_timestamp();
        scanf("%u ", &info.moments[0].y);

        info.moments[1].x = read_timestamp();
        scanf("%u\n", &info.moments[1].y);

        if (info.moments[0].x > info.moments[1].x)
            std::swap(info.moments[0], info.moments[1]);
    }

    char s[1001], t[1001];
    scanf("%s\n", s);
    scanf("%s\n", t);

    solve(infos, s, t);

    return 0;
}
