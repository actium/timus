#include <iostream>
#include <string>
#include <vector>

struct Layer {
    std::vector<std::string> grid;
    std::vector<std::vector<bool>> visited;

    Layer(size_t a, size_t b)
        : grid(a)
        , visited(a, std::vector<bool>(b))
    {}
};

struct Position {
    unsigned x;
    unsigned y;
    unsigned z;
};

bool operator ==(const Position& lhs, const Position& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

std::istream& operator >>(std::istream& input_stream, Position& position)
{
    input_stream >> position.x >> position.y >> position.z;

    --position.x;
    --position.y;
    --position.z;

    return input_stream;
}

struct Action {
    const char* name;
    int dx;
    int dy;
    int dz;
};

constexpr Action actions[] = {
    { "walk north", -1,  0, 0 },
    { "walk east",   0,  1, 0 },
    { "walk south",  1,  0, 0 },
    { "walk west",   0, -1, 0 },

    { "jump north", -2,  0, 0 },
    { "jump east",   0,  2, 0 },
    { "jump south",  2,  0, 0 },
    { "jump west",   0, -2, 0 },

    { "drop north", -1,  0, -1 },
    { "drop east",   0,  1, -1 },
    { "drop south",  1,  0, -1 },
    { "drop west",   0, -1, -1 },

    { "climb north", -1,  0, 1 },
    { "climb east",   0,  1, 1 },
    { "climb south",  1,  0, 1 },
    { "climb west",   0, -1, 1 },
};

Position simulate_action(Position p, unsigned a)
{
    return { p.x + actions[a].dx, p.y + actions[a].dy, p.z + actions[a].dz };
}

void solve(std::vector<Layer>& maze, const Position& s, const Position& t)
{
    const auto is_empty = [&](unsigned x, unsigned y, unsigned z) {
        const auto sz = maze.size(), sx = maze[0].grid.size(), sy = maze[0].grid[0].size();
        return x < sx && y < sy && z < sz && maze[z].grid[x][y] == '.';
    };

    std::vector<std::pair<unsigned, unsigned>> moves;
    std::vector<std::pair<unsigned, Position>> q;

    const auto enqueue = [&](unsigned x, unsigned y, unsigned z, unsigned action, unsigned source) {
        if (is_empty(x, y, z) && (z == 0 || !is_empty(x, y, z-1)) && !maze[z].visited[x][y]) {
            q.emplace_back(moves.size(), Position { x, y, z });
            moves.emplace_back(source, action);
            maze[z].visited[x][y] = true;
        }
    };

    const auto answer = [&](unsigned x) {
        std::vector<std::string> path;
        while (x != ~0u) {
            path.emplace_back();
            path.back().append(actions[moves[x].second].name);
            x = moves[x].first;
        }

        std::cout << "YES" << '\n';
        std::cout << path.size() << '\n';
        for (auto it = path.rbegin(); it != path.rend(); ++it)
            std::cout << *it << '\n';
    };

    q.emplace_back(~0u, s);

    for (size_t i = 0; i < q.size(); ++i) {
        const auto [source, p0] = q[i];

        if (p0 == t)
            return answer(source);

        for (unsigned a = 0; a < 4; ++a) {
            const Position p1 = simulate_action(p0, a), p2 = simulate_action(p1, a);

            if (is_empty(p1.x, p1.y, p1.z) && is_empty(p1.x, p1.y, p1.z-1))
                enqueue(p2.x, p2.y, p2.z, 4 + a, source);

            if (is_empty(p1.x, p1.y, p1.z))
                enqueue(p1.x, p1.y, p1.z-1, 8 + a, source);

            if (is_empty(p0.x, p0.y, p0.z+1))
                enqueue(p1.x, p1.y, p1.z+1, 12 + a, source);

            enqueue(p1.x, p1.y, p1.z, a, source);
        }
    }

    std::cout << "NO" << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t a, b, h;
    std::cin >> a >> b >> h;

    std::vector<Layer> maze(h, { a, b });
    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < a; ++j)
            std::cin >> maze[i].grid[j];
    }

    Position s, t;
    std::cin >> s >> t;

    solve(maze, s, t);

    return 0;
}
