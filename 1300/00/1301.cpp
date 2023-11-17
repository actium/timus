#include <iostream>
#include <queue>
#include <map>
#include <vector>

struct Position {
    unsigned x;
    unsigned y;
};

struct Dice {
    Position p;
    unsigned s = (0 << 0) | (1 << 5) | (2 << 10) | (4 << 15) | (8 << 20) | (16 << 25);

    unsigned translate(unsigned u, unsigned v) const
    {
        return ((s >> u) & 31) << v;
    }

    Dice roll_x(bool cw) const
    {
        Dice d = *this;
        if (cw) {
            ++d.p.y;
            d.s = translate(20, 0) | translate(0, 5) | translate(10, 10) | translate(15, 15) | translate(25, 20) | translate(5, 25);
        } else {
            --d.p.y;
            d.s = translate(5, 0) | translate(25, 5) | translate(10, 10) | translate(15, 15) | translate(0, 20) | translate(20, 25);
        }
        return d;
    }

    Dice roll_y(bool cw) const
    {
        Dice d = *this;
        if (cw) {
            --d.p.x;
            d.s = translate(15, 0) | translate(5, 5) | translate(0, 10) | translate(25, 15) | translate(20, 20) | translate(10, 25);
        } else {
            ++d.p.x;
            d.s = translate(10, 0) | translate(5, 5) | translate(25, 10) | translate(0, 15) | translate(20, 20) | translate(15, 25);
        }
        return d;
    }
};

bool operator <(const Dice& lhs, const Dice& rhs)
{
    if (lhs.s != rhs.s)
        return lhs.s < rhs.s;

    return std::make_pair(lhs.p.x, lhs.p.y) < std::make_pair(rhs.p.x, rhs.p.y);
}

int main()
{
    unsigned w, h;
    std::cin >> w >> h;

    Position s;
    std::cin >> s.x >> s.y;

    Position t;
    std::cin >> t.x >> t.y;

    std::vector<std::vector<std::vector<Position>>> g(h, std::vector<std::vector<Position>>(w));
    for (std::string v; std::cin >> v; ) {
        if (v == "v")
            continue;

        if (v == "h")
            break;

        unsigned c = std::stoi(v), r;
        std::cin >> r;

        g[r-1][c-1].push_back({c + 1, r});
        g[r-1][c].push_back({c, r});
    }
    for (unsigned c, r; std::cin >> c >> r; ) {
        g[r-1][c-1].push_back({c, r + 1});
        g[r][c-1].push_back({c, r});
    }

    const auto test = [&](const Position& p, int dx, int dy) {
        const Position q = { p.x + dx, p.y + dy };
        if (q.x == 0 || q.x > w || q.y == 0 || q.y > h)
            return false;

        for (const Position& t : g[p.y-1][p.x-1]) {
            if (t.x == q.x && t.y == q.y)
                return false;
        }
        return true;
    };

    std::queue<std::pair<Dice, unsigned>> q;
    std::map<Dice, unsigned> d;

    const auto enqueue = [&](const Dice& dice, unsigned k) {
        const auto s = d.emplace(dice, k);
        if (s.second || k < s.first->second) {
            s.first->second = k;
            q.emplace(dice, k);
        }
    };

    enqueue({s.x, s.y}, 0);
    while (!q.empty()) {
        const std::pair<Dice, unsigned> p = q.front();
        q.pop();

        if (p.first.p.x == t.x && p.first.p.y == t.y && (p.first.s & 31) == 0) {
            std::cout << p.second << '\n';
            return 0;
        }

        if (test(p.first.p, 0, 1))
            enqueue(p.first.roll_x(true), p.second + 1);

        if (test(p.first.p, 0, -1))
            enqueue(p.first.roll_x(false), p.second + 1);

        if (test(p.first.p, 1, 0))
            enqueue(p.first.roll_y(false), p.second + 1);

        if (test(p.first.p, -1, 0))
            enqueue(p.first.roll_y(true), p.second + 1);
    }

    std::cout << "No solution" << '\n';

    return 0;
}
