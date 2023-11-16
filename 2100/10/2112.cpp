#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

struct Record {
    size_t s;
    size_t t;
    unsigned a;
};

std::vector<std::vector<size_t>> solve(size_t n, const std::vector<Record>& log)
{
    std::vector<size_t> t(n);
    for (size_t i = 0; i < n; ++i)
        t[i] = i;

    const auto resolve = [&](size_t x) {
        while (x != t[x])
            x = std::exchange(t[x], t[t[x]]);

        return x;
    };

    const auto unite = [&](size_t u, size_t v) {
        t[resolve(u)] = resolve(v);
    };

    std::vector<int> h(n, 3);
    for (const Record& r : log) {
        if (h[r.s] < 2)
            return {};

        switch (r.a) {
            case 0:
                h[r.t] -= 1;
                break;
            case 1:
                h[r.t] -= 2;
                break;
            case 2:
                if (h[r.t] != 1)
                    return {};

                h[r.t] = 2;
                unite(r.s, r.t);
                break;
            case 3:
                h[r.t] = 3;
                break;
        }
    }

    std::vector<std::vector<size_t>> teams(n);
    for (size_t i = 0; i < n; ++i)
        teams[resolve(i)].push_back(i);

    std::sort(teams.begin(), teams.end(), [](const std::vector<size_t>& a, const std::vector<size_t>& b) {
        return a.size() > b.size();
    });

    for (size_t i = 0; i < teams.size(); ++i) {
        while (teams[i].size() < 4) {
            teams[i].insert(teams[i].end(), teams.back().begin(), teams.back().end());
            teams.pop_back();
        }

        if (teams[i].size() != 4)
            return {};
    }

    return teams;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::string> p(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> p[i];

    std::map<std::string_view, size_t> x;
    for (size_t i = 0; i < n; ++i)
        x[p[i]] = i;

    size_t m;
    std::cin >> m;

    std::vector<Record> log(m);
    for (size_t i = 0; i < m; ++i) {
        std::string s, a, t, p;
        std::cin >> s >> a;

        log[i].s = x[s];

        switch (a[0]) {
            case 'H':
                std::cin >> t >> a >> p;
                log[i].t = x[t];
                log[i].a = (p[0] == 'B' ? 0 : 1);
                break;

            case 'R':
                std::cin >> t;
                log[i].t = x[t];
                log[i].a = 2;
                break;

            case 'U':
                std::cin >> a;
                log[i].t = log[i].s;
                log[i].a = 3;
                break;
        }
    }

    const std::vector<std::vector<size_t>> t = solve(n, log);
    if (t.empty()) {
        std::cout << "FAKE" << '\n';
    } else {
        std::cout << "CORRECT" << '\n';
        for (const std::vector<size_t>& v : t) {
            for (const size_t i : v)
                std::cout << p[i] << ' ';

            std::cout << '\n';
        }
    }

    return 0;
}
