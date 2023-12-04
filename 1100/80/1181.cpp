#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::pair<unsigned, unsigned>> solve(const std::string& c)
{
    const size_t n = c.length();

    const auto adjacent = [n](unsigned u, unsigned v) {
        return u + 1 == v || u == v + 1 || u == 1 && v == n || u == n && v == 1;
    };

    std::vector<size_t> p[3];
    for (size_t i = 0; i < n; ++i) {
        switch (c[i]) {
            case 'R': p[0].push_back(i + 1); break;
            case 'G': p[1].push_back(i + 1); break;
            case 'B': p[2].push_back(i + 1); break;
        }
    }

    for (size_t i = 0; i < 3; ++i)
        std::reverse(p[i].begin(), p[i].end());

    std::vector<std::pair<unsigned, unsigned>> d;
    {
        while (p[0].size() > 1 && p[1].size() > 1 && p[2].size() > 1) {
            size_t s[3] = { 0, 1, 2 };
            std::sort(std::begin(s), std::end(s), [&](size_t i, size_t j) { return p[i].back() < p[j].back(); });

            const unsigned u = p[s[0]].back(), v = p[s[2]].back();
            for (size_t i = 0; i < 2; ++i) {
                while (!p[s[i]].empty() && p[s[i]].back() < v) {
                    if (!adjacent(p[s[i]].back(), v))
                        d.emplace_back(p[s[i]].back(), v);

                    p[s[i]].pop_back();
                }
            }
            p[s[0]].push_back(u);
        }

        size_t s[3] = { 0, 1, 2 };
        std::sort(std::begin(s), std::end(s), [&](size_t i, size_t j) { return p[i].size() < p[j].size(); });

        if (!p[s[0]].empty()) {
            const unsigned v = p[s[0]].back();
            for (size_t i = 1; i < 3; ++i) {
                for (const unsigned x : p[s[i]]) {
                    if (!adjacent(x, v))
                        d.emplace_back(std::min(x, v), std::max(x, v));
                }
            }
        }
    }
    return d;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::string c;
    std::cin >> c;

    std::vector<std::pair<unsigned, unsigned>> d;
    for (const char b : { 'R', 'G', 'B' }) {
        const size_t x = c.find(b);

        d = solve(c.substr(x) + c.substr(0, x));
        if (d.size() != n - 3)
            continue;

        std::cout << d.size() << '\n';
        for (const std::pair<unsigned, unsigned>& p : d)
            std::cout << 1 + (p.first + x - 1) % n << ' ' << 1 + (p.second + x - 1) % n << '\n';

        break;
    }

    return 0;
}
