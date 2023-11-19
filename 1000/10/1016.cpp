#include <iostream>
#include <set>
#include <string>
#include <vector>

constexpr unsigned oo = ~0u >> 1;

struct Dice {
    unsigned edges[6];
    unsigned transitions[4];
};

constexpr Dice dices[24] = {
    { { 0, 1, 2, 3, 4, 5 }, {  1,  2,  3,  4 } },
    { { 4, 2, 0, 3, 1, 5 }, {  5,  6,  0,  7 } },
    { { 0, 1, 5, 2, 3, 4 }, {  8,  9, 10,  0 } },
    { { 2, 4, 1, 3, 0, 5 }, {  0, 11,  5, 12 } },
    { { 0, 1, 3, 4, 5, 2 }, { 13,  0, 14,  9 } },
    { { 1, 0, 4, 3, 2, 5 }, {  3, 15,  1, 16 } },
    { { 4, 2, 5, 0, 3, 1 }, { 17, 18, 19,  1 } },
    { { 4, 2, 3, 1, 5, 0 }, { 20,  1, 21, 18 } },
    { { 3, 5, 0, 2, 1, 4 }, { 16, 17,  2, 21 } },
    { { 0, 1, 4, 5, 2, 3 }, { 22,  4, 18,  2 } },
    { { 5, 3, 1, 2, 0, 4 }, {  2, 20, 16, 19 } },
    { { 2, 4, 5, 1, 3, 0 }, { 21, 22, 20,  3 } },
    { { 2, 4, 3, 0, 5, 1 }, { 19,  3, 17, 22 } },
    { { 5, 3, 0, 4, 1, 2 }, { 15, 19,  4, 20 } },
    { { 3, 5, 1, 4, 0, 2 }, {  4, 21, 15, 17 } },
    { { 1, 0, 5, 4, 3, 2 }, { 14, 23, 13,  5 } },
    { { 1, 0, 3, 2, 5, 4 }, { 10,  5,  8, 23 } },
    { { 3, 5, 4, 0, 2, 1 }, { 12, 14,  6,  8 } },
    { { 4, 2, 1, 5, 0, 3 }, {  9,  7, 23,  6 } },
    { { 5, 3, 2, 0, 4, 1 }, {  6, 10, 12, 13 } },
    { { 5, 3, 4, 1, 2, 0 }, { 11, 13,  7, 10 } },
    { { 3, 5, 2, 1, 4, 0 }, {  7,  8, 11, 14 } },
    { { 2, 4, 0, 5, 1, 3 }, { 23, 12,  9, 11 } },
    { { 1, 0, 2, 5, 4, 3 }, { 18, 16, 22, 15 } },
};

struct State {
    unsigned s;
    unsigned v = oo;
};

bool operator <(const State& lhs, const State& rhs)
{
    return lhs.v < rhs.v;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s, t;
    std::cin >> s >> t;

    unsigned v[6];
    for (size_t i = 0; i < 6; ++i)
        std::cin >> v[i];

    std::set<std::pair<unsigned, unsigned>> q;
    State d[24][64];

    const auto enqueue = [&](unsigned c, unsigned p, unsigned s, unsigned u) {
        const unsigned value = u + v[dices[c].edges[4]];
        if (d[c][p].v <= value)
            return;

        if (d[c][p].v != oo)
            q.erase(std::make_pair(d[c][p].v, c * 64 + p));

        q.emplace(value, c * 64 + p);
        d[c][p].v = value;
        d[c][p].s = s;
    };

    const unsigned sp = (s[0] - 'a') + (s[1] - '1') * 8;
    const unsigned tp = (t[0] - 'a') + (t[1] - '1') * 8;

    enqueue(0, sp, oo, 0);
    while (!q.empty()) {
        const std::pair<unsigned, unsigned> u = *q.begin();
        q.erase(q.begin());

        unsigned c = u.second / 64, p = u.second % 64;
        if (p == tp) {
            std::vector<std::pair<char, char>> path;
            for (unsigned x = u.second; x != oo; x = d[c][p].s) {
                c = x / 64, p = x % 64;
                path.emplace_back('a' + p % 8, '1' + p / 8);
            }

            std::cout << u.first;
            while (!path.empty()) {
                std::cout << ' ' << path.back().first << path.back().second;
                path.pop_back();
            }
            break;
        }

        if (p <= 55)
            enqueue(dices[c].transitions[0], p + 8, c * 64 + p, u.first);

        if (p % 8 < 7)
            enqueue(dices[c].transitions[1], p + 1, c * 64 + p, u.first);

        if (p >= 8)
            enqueue(dices[c].transitions[2], p - 8, c * 64 + p, u.first);

        if (p % 8 > 0)
            enqueue(dices[c].transitions[3], p - 1, c * 64 + p, u.first);
    }

    return 0;
}
