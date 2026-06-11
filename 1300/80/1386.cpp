#include <array>
#include <iostream>
#include <vector>

struct Position {
    unsigned r;
    unsigned c;
};

std::istream& operator >>(std::istream& input_stream, Position& position)
{
    input_stream >> position.r >> position.c;
    --position.r;
    --position.c;
    return input_stream;
}

struct Maze : std::array<std::vector<std::vector<Position>>, 4> {
    unsigned width;
    unsigned height;

    Maze(size_t n, size_t m)
        : width(m)
        , height(n)
    {
        for (size_t k = 0; k < 4; ++k)
            (*this)[k].resize(height, std::vector<Position>(width));
    }
};

void solve(const Maze& maze, const std::vector<unsigned>& commands)
{
    const size_t s = commands.size();

    std::vector<bool> qs[2];
    qs[1].resize(maze.width * maze.height, true);
    for (size_t t = 0, x = 0; t < s; ++t, x ^= 1) {
        qs[x].assign(maze.width * maze.height, false);

        for (unsigned r = 0, i = 0; r < maze.height; ++r) {
            for (unsigned c = 0; c < maze.width; ++c, ++i) {
                if (qs[x^1][i]) {
                    const auto& p = maze[commands[t]-1][r][c];
                    qs[x][p.r * maze.width + p.c] = true;
                }
            }
        }
    }

    std::vector<Position> ps;
    for (unsigned r = 0, i = 0; r < maze.height; ++r) {
        for (unsigned c = 0; c < maze.width; ++c, ++i) {
            if (qs[s&1^1][i])
                ps.push_back({ 1+r, 1+c });
        }
    }

    std::cout << ps.size() << '\n';
    for (const auto& p : ps)
        std::cout << p.r << ' ' << p.c << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    Maze maze(n, m);
    for (size_t k = 0; k < 4; ++k) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j)
                std::cin >> maze[k][i][j];
        }
    }

    size_t s;
    std::cin >> s;

    std::vector<unsigned> commands(s);
    for (size_t i = 0; i < s; ++i)
        std::cin >> commands[i];

    solve(maze, commands);

    return 0;
}
