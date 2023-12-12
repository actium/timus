#include <iostream>
#include <vector>

struct Record {
    size_t u;
    size_t v;
    int d;
};

void solve(size_t n, const std::vector<Record>& rs)
{
    const size_t m = rs.size();

    std::vector<std::pair<size_t, int>> data(n);
    for (size_t i = 0; i < n; ++i)
        data[i].first = i;

    const auto lookup = [&](size_t x) {
        int s = 0;

        size_t rx = x;
        while (rx != data[rx].first) {
            s += data[rx].second;
            rx = data[rx].first;
        }

        int d = 0;
        while (x != rx) {
            const auto t = data[x];
            data[x].first = rx;
            data[x].second = s - d;
            d += t.second;
            x = t.first;
        }

        return std::make_pair(rx, s + data[rx].second);
    };

    for (size_t i = 0; i < m; ++i) {
        const auto ru = lookup(rs[i].u), rv = lookup(rs[i].v);
        if (ru.first != rv.first) {
            data[ru.first].second = -ru.second;
            data[ru.first].first = rs[i].u;
            data[rs[i].u].second = rv.second + rs[i].d;
            data[rs[i].u].first = rv.first;
            continue;
        }
        if (ru.second != rv.second + rs[i].d) {
            std::cout << "Impossible after " << i+1 << " statements" << '\n';
            return;
        }
    }

    for (size_t i = 0; i < n; ++i) {
        const auto r = lookup(i);
        if (r.second < 0)
            data[r.first].second -= r.second;
    }

    for (size_t i = 1; i < n; ++i) {
        const auto ri = lookup(i), r0 = lookup(0);
        if (ri.first != r0.first)
            continue;

        const int s = ri.second - r0.second;
        if (s < 0 || s > 1000000000) {
            std::cout << "Impossible after " << m << " statements" << '\n';
            return;
        }
    }

    std::cout << "Possible" << '\n';
    for (size_t i = 0; i < n; ++i)
        std::cout << lookup(i).second << '\n';
}

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    std::vector<Record> rs(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> rs[i].u >> rs[i].v >> rs[i].d;

    solve(n, rs);

    return 0;
}
