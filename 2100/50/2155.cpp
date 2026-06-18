#include <iostream>
#include <string>
#include <vector>

using integer = long long;

constexpr unsigned oo = ~0u;

struct Position {
    unsigned r;
    unsigned c;
};

std::istream& operator >>(std::istream& input_stream, Position& position)
{
    return input_stream >> position.r >> position.c;
}

std::vector<std::vector<integer>> compute_distances(const std::vector<std::vector<unsigned>>& bs, Position s)
{
    const size_t h = bs.size(), w = bs[0].size();

    std::vector<std::vector<integer>> distances(h, std::vector<integer>(w, 1000000000000000));
    {
        std::vector<Position> q;

        const auto enqueue = [&](unsigned r, unsigned c, integer d) {
            if (r < h && c < w && d + bs[r][c] < distances[r][c]) {
                distances[r][c] = d + bs[r][c];
                q.push_back({ r, c });
            }
        };

        enqueue(s.r-1, s.c-1, -integer(bs[s.r-1][s.c-1]));

        for (size_t i = 0; i < q.size(); ++i) {
            const auto [r, c] = q[i];
            const auto d = distances[r][c];

            enqueue(r-1, c, d);
            enqueue(r, c+1, d);
            enqueue(r+1, c, d);
            enqueue(r, c-1, d);
        }
    }
    return distances;
}

struct Period {
    unsigned t = oo;
    unsigned d = 0;
};

std::vector<std::vector<Period>> compute_periods(const std::vector<std::string>& ds, Position s)
{
    const size_t h = ds.size(), w = ds[0].size();

    std::vector<std::vector<Period>> periods(h, std::vector<Period>(w));
    {
        std::vector<std::pair<Position, unsigned>> q;

        const auto enqueue = [&](unsigned r, unsigned c, unsigned t) {
            if (r >= h || c >= w || periods[r][c].d != 0)
                return;

            if (t < periods[r][c].t) {
                periods[r][c].t = t;
            } else {
                periods[r][c].d = t - periods[r][c].t;
            }

            q.emplace_back(Position { r, c }, t);
        };

        enqueue(s.r-1, s.c-1, 0);

        for (size_t i = 0; i < q.size(); ++i) {
            const auto [p, t] = q[i];
            switch (ds[p.r][p.c]) {
                case 'U': enqueue(p.r - 1, p.c, t + 1); break;
                case 'R': enqueue(p.r, p.c + 1, t + 1); break;
                case 'D': enqueue(p.r + 1, p.c, t + 1); break;
                case 'L': enqueue(p.r, p.c - 1, t + 1); break;
            }
        }
    }
    return periods;
}

integer solve(const std::vector<std::vector<unsigned>>& bs, const std::vector<std::string>& ds, Position u, Position v)
{
    const size_t h = bs.size(), w = bs[0].size();

    const auto distances = compute_distances(bs, u);
    const auto periods = compute_periods(ds, v);

    integer d = -1;
    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j) {
            if (periods[i][j].t == oo)
                continue;

            integer t = periods[i][j].t;
            if (t < distances[i][j] && periods[i][j].d != 0) {
                const auto k = (distances[i][j] - t + periods[i][j].d - 1) / periods[i][j].d;
                t += k * periods[i][j].d;
            }

            if (distances[i][j] <= t && (d == -1 || t < d))
                d = t;
        }
    }
    return d;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t h, w;
    std::cin >> h >> w;

    Position u, v;
    std::cin >> u >> v;

    std::vector<std::vector<unsigned>> bs(h, std::vector<unsigned>(w));
    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j)
            std::cin >> bs[i][j];
    }

    std::vector<std::string> ds(h);
    for (size_t i = 0; i < h; ++i)
        std::cin >> ds[i];

    std::cout << solve(bs, ds, u, v);

    return 0;
}
