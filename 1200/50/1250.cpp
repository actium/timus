#include <iostream>
#include <string>
#include <vector>

constexpr std::pair<int, int> d[8] = {
    { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 },
    { -1, 1 }, { 1, 1 }, { 1, -1 }, { -1, -1 },
};

struct Cell {
    char t = '#';
    unsigned z = 0;
};

void paint(std::vector<std::vector<Cell>>& g, size_t r, size_t c, unsigned z, std::vector<std::pair<size_t, size_t>>& q)
{
    g[r][c].z = z;

    for (size_t i = (g[r][c].t == '#' ? 4 : 8); i-- > 0; ) {
        const size_t nr = r + d[i].first, nc = c + d[i].second;
        if (nr >= g.size() || nc >= g[0].size() || g[nr][nc].z != 0)
            continue;

        if (g[nr][nc].t == g[r][c].t)
            paint(g, nr, nc, z, q);
        else
            q.emplace_back(nr, nc);
    }
}

unsigned search(std::vector<std::vector<Cell>>& g, size_t r, size_t c, std::vector<unsigned>& s)
{
    const size_t z = s.size();

    s.push_back(g[r][c].t == '#');

    std::vector<std::pair<size_t, size_t>> q;
    paint(g, r, c, s.size(), q);
    for (const std::pair<size_t, size_t>& p : q) {
        if (g[p.first][p.second].z == 0)
            s[z] += search(g, p.first, p.second, s);
    }

    return s[z];
}

unsigned solve(std::vector<std::vector<Cell>>& g, size_t r, size_t c)
{
    std::vector<unsigned> s;
    search(g, 0, 0, s);
    return s[g[r][c].z-1];
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned w, h, x, y;
    std::cin >> w >> h >> x >> y;

    std::vector<std::vector<Cell>> g(h + 2, std::vector<Cell>(w + 2));
    for (unsigned i = 1; i <= h; ++i) {
        for (unsigned j = 1; j <= w; ++j)
            std::cin >> g[i][j].t;

        std::cin >> std::ws;
    }

    std::cout << solve(g, y, x) << '\n';

    return 0;
}
