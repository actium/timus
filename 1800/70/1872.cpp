#include <algorithm>
#include <iostream>
#include <vector>

struct Room {
    size_t i;
    unsigned s;
};

struct Team {
    size_t i;
    unsigned lb;
    unsigned ub;
};

bool cycle_exists(const std::vector<std::vector<size_t>>& g, size_t u, std::vector<unsigned>& s)
{
    if (s[u] == 0) {
        s[u] = 1;
        for (const size_t v : g[u]) {
            if (cycle_exists(g, v, s))
                return true;
        }
        s[u] = 2;
    }
    return s[u] == 1;
}

void solve(std::vector<Room>& rooms, std::vector<Team>& teams)
{
    const size_t n = rooms.size();

    std::sort(rooms.begin(), rooms.end(), [](const Room& lhs, const Room& rhs) {
        return lhs.s < rhs.s;
    });

    std::sort(teams.begin(), teams.end(), [](const Team& lhs, const Team& rhs) {
        return lhs.ub < rhs.ub;
    });

    std::vector<unsigned> assignments(n);
    for (const Team& team : teams) {
        auto it = std::lower_bound(rooms.begin(), rooms.end(), team.lb, [](const Room& room, unsigned b) {
            return room.s < b;
        });
        while (it != rooms.end() && assignments[it->i] != 0)
            ++it;

        if (it == rooms.end() || team.ub < it->s) {
            std::cout << "Let's search for another office." << '\n';
            return;
        }

        assignments[it->i] = 1 + team.i;
    }

    std::vector<std::vector<size_t>> g(2 * n);
    for (const Team& team : teams) {
        for (const Room& room : rooms) {
            if (room.s < team.lb || team.ub < room.s)
                continue;

            if (assignments[room.i] == 1 + team.i)
                g[n+room.i].push_back(team.i);
            else
                g[team.i].push_back(n+room.i);
        }
    }

    std::vector<unsigned> s(2 * n);
    for (size_t i = 0; i < 2 * n; ++i) {
        if (cycle_exists(g, i, s)) {
            std::cout << "Ask Shiftman for help." << '\n';
            return;
        }
    }

    std::vector<unsigned> p(n);
    for (const Room& room : rooms)
        p[assignments[room.i]-1] = 1 + room.i;

    std::cout << "Perfect!" << '\n';
    for (const unsigned x : p)
        std::cout << x << ' ';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Room> rooms(n);
    for (size_t i = 0; i < n; ++i) {
        rooms[i].i = i;
        std::cin >> rooms[i].s;
    }

    std::vector<Team> teams(n);
    for (size_t i = 0; i < n; ++i) {
        teams[i].i = i;
        std::cin >> teams[i].lb >> teams[i].ub;
    }

    solve(rooms, teams);

    return 0;
}
