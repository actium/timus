#include <iostream>
#include <set>
#include <string>
#include <vector>

using position_t = std::pair<unsigned, unsigned>;
using distance_t = std::pair<unsigned, unsigned>;

constexpr distance_t oo = { ~0u, ~0u };

double evaluate(const distance_t d)
{
    return d.first + d.second * 1.41421356237;
}

void paint(std::vector<std::string>& g, size_t i, size_t j, char c)
{
    if (i >= g.size() || j >= g[i].size() || g[i][j] != '.')
        return;

    g[i][j] = c;

    for (int dx = -1; dx <= +1; ++dx) {
        for (int dy = -1; dy <= +1; ++dy) {
            if (dx != 0 || dy != 0)
                paint(g, i + dx, j + dy, c);
        }
    }
}

struct Node {
    position_t p;
    distance_t d;
    distance_t h;
};

bool operator <(const Node& lhs, const Node& rhs)
{
    const distance_t ld = { lhs.d.first + lhs.h.first, lhs.d.second + lhs.h.second };
    const distance_t rd = { rhs.d.first + rhs.h.first, rhs.d.second + rhs.h.second };
    if (ld != rd)
        return evaluate(ld) < evaluate(rd);

    if (lhs.h != rhs.h)
        return evaluate(lhs.h) < evaluate(rhs.h);

    return lhs.p < rhs.p;
}

distance_t search(const std::vector<std::string>& g, const position_t& s, const position_t& t)
{
    const size_t n = g.size(), m = g[0].length();

    const auto heuristic = [&](const position_t& p) {
        const unsigned dx = (p.first < t.first ? t.first - p.first : p.first - t.first);
        const unsigned dy = (p.second < t.second ? t.second - p.second : p.second - t.second);
        return std::make_pair(std::max(dx, dy) - std::min(dx, dy), std::min(dx, dy));
    };

    std::set<Node> q;
    std::vector<std::vector<distance_t>> v(n, std::vector<distance_t>(m, oo));

    const auto enqueue = [&](const position_t& p, const distance_t& d, int dx, int dy) {
        if (p.first + dx == 0 || p.first + dx > n)
            return;

        if (p.second + dy == 0 || p.second + dy > m)
            return;

        if (g[p.first+dx-1][p.second+dy-1] != g[p.first-1][p.second-1])
            return;

        Node node;
        node.p = { p.first + dx, p.second + dy };
        node.d = { d.first + (dx == 0 || dy == 0), d.second + (dx != 0 && dy != 0) };
        node.h = heuristic(node.p);

        if (v[node.p.first-1][node.p.second-1] != oo) {
            if (evaluate(v[node.p.first-1][node.p.second-1]) <= evaluate(node.d))
                return;

            q.erase({ node.p, v[node.p.first-1][node.p.second-1], node.h });
        }

        q.insert(node);
        v[node.p.first-1][node.p.second-1] = node.d;
    };

    const auto dequeue = [&] {
        const Node x = *q.begin();
        q.erase(q.begin());
        return x;
    };

    enqueue(s, distance_t(-1, 0), 0, 0);
    while (q.begin()->p != t) {
        const Node x = dequeue();

        for (int dx = -1; dx <= +1; ++dx) {
            for (int dy = -1; dy <= +1; ++dy) {
                if (dx != 0 || dy != 0)
                    enqueue(x.p, x.d, dx, dy);
            }
        }
    }

    return q.begin()->d;
}

double solve(std::vector<std::string>& g, const std::vector<position_t>& p)
{
    const size_t n = g.size(), m = g[0].length(), k = p.size();

    for (size_t i = 0, c = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            if (g[i][j] == '.')
                paint(g, i, j, 'a' + c++);
        }
    }

    distance_t d = { 0, 0 };
    for (size_t i = 0, j = 1; j < k; ++j) {
        if (g[p[j].first-1][p[j].second-1] != g[p[i].first-1][p[i].second-1])
            continue;

        const distance_t s = search(g, p[i], p[j]);
        d.first += s.first;
        d.second += s.second;

        i = j;
    }

    return evaluate(d);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m, k;
    std::cin >> n >> m >> k;

    double v;
    std::cin >> v;

    std::vector<std::string> g(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> g[i];

    std::vector<position_t> p(1 + k);
    for (size_t i = 0; i <= k; ++i) {
        std::cin >> p[i].first >> p[i].second;

        std::swap(p[i].first, p[i].second);
    }

    std::cout << std::fixed << solve(g, p) / v << '\n';

    return 0;
}
