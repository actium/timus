#include <iostream>
#include <vector>

using grid_t = std::vector<std::vector<unsigned>>;
using cell_t = std::pair<size_t, size_t>;

void paint(grid_t& g, size_t i, size_t j)
{
    static unsigned c = 0;

    ++c;

    g[i + 0][j + 0] = c;
    g[i + 0][j + 1] = c;
    g[i + 1][j + 0] = c;
    g[i + 1][j + 1] = c;
}

void fill(grid_t& g, const cell_t& s, unsigned w, const cell_t& x)
{
    w /= 2;
    if (w == 1)
        return paint(g, s.first, s.second);

    const unsigned dr = (x.first - s.first) / w, dc = (x.second - s.second) / w;
    switch (dr * 2 + dc) {
        case 0:
            fill(g, std::make_pair(s.first + 0, s.second + w), w, std::make_pair(s.first + w - 1, s.second + w));
            fill(g, std::make_pair(s.first + w, s.second + 0), w, std::make_pair(s.first + w, s.second + w - 1));
            fill(g, std::make_pair(s.first + w, s.second + w), w, std::make_pair(s.first + w, s.second + w));
            paint(g, s.first + w - 1, s.second + w - 1);
            fill(g, std::make_pair(s.first + 0, s.second + 0), w, x);
            break;

        case 1:
            fill(g, std::make_pair(s.first + 0, s.second + 0), w, std::make_pair(s.first + w - 1, s.second + w - 1));
            fill(g, std::make_pair(s.first + w, s.second + 0), w, std::make_pair(s.first + w, s.second + w - 1));
            fill(g, std::make_pair(s.first + w, s.second + w), w, std::make_pair(s.first + w, s.second + w));
            paint(g, s.first + w - 1, s.second + w - 1);
            fill(g, std::make_pair(s.first + 0, s.second + w), w, x);
            break;

        case 2:
            fill(g, std::make_pair(s.first + 0, s.second + 0), w, std::make_pair(s.first + w - 1, s.second + w - 1));
            fill(g, std::make_pair(s.first + 0, s.second + w), w, std::make_pair(s.first + w - 1, s.second + w));
            fill(g, std::make_pair(s.first + w, s.second + w), w, std::make_pair(s.first + w, s.second + w));
            paint(g, s.first + w - 1, s.second + w - 1);
            fill(g, std::make_pair(s.first + w, s.second + 0), w, x);
            break;

        case 3:
            fill(g, std::make_pair(s.first + 0, s.second + 0), w, std::make_pair(s.first + w - 1, s.second + w - 1));
            fill(g, std::make_pair(s.first + w, s.second + 0), w, std::make_pair(s.first + w, s.second + w - 1));
            fill(g, std::make_pair(s.first + 0, s.second + w), w, std::make_pair(s.first + w - 1, s.second + w));
            paint(g, s.first + w - 1, s.second + w - 1);
            fill(g, std::make_pair(s.first + w, s.second + w), w, x);
            break;
    }
}

void solve(unsigned n, unsigned r, unsigned c)
{
    const unsigned w = 1 << n;

    grid_t g(w, std::vector<unsigned>(w));
    fill(g, std::make_pair(0, 0), w, std::make_pair(--r, --c));
    g[r][c] = 0;

    for (unsigned i = 0; i < w; ++i) {
        for (unsigned j = 0; j < w; ++j)
            std::cout << g[i][j] << ' ';

        std::cout << '\n';
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned n;
    std::cin >> n;

    unsigned r, c;
    std::cin >> r >> c;

    solve(n, r, c);

    return 0;
}
