#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void solve(const std::vector<std::pair<std::string, unsigned>>& ws, const std::vector<std::string>& qs)
{
    const size_t n = ws.size(), m = qs.size();

    std::vector<size_t> ps[15];
    for (size_t i = 0; i < n; ++i) {
        for (size_t k = 1; k <= 15 && ws[i].first.length() >= k; ++k)
            ps[k-1].push_back(i);
    }

    for (size_t k = 1; k <= 15; ++k) {
        std::sort(ps[k-1].begin(), ps[k-1].end(), [&](size_t i, size_t j) {
            const int d = ws[i].first.compare(0, k, ws[j].first, 0, k);
            if (d != 0)
                return d < 0;

            if (ws[i].second != ws[j].second)
                return ws[i].second > ws[j].second;

            return ws[i].first < ws[j].first;
        });
    }

    for (size_t i = 0; i < m; ++i) {
        const std::vector<size_t>& p = ps[qs[i].length()-1];

        auto it = std::lower_bound(p.begin(), p.end(), qs[i], [&](size_t i, const std::string& q) {
            return ws[i].first.compare(0, q.length(), q) < 0;
        });

        for (size_t k = 0; k < 10; ++k, ++it) {
            if (it == p.end() || ws[*it].first.compare(0, qs[i].length(), qs[i]) != 0)
                break;

            std::cout << ws[*it].first << '\n';
        }

        if (i + 1 < m)
            std::cout << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::pair<std::string, unsigned>> ws(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> ws[i].first >> ws[i].second;

    size_t m;
    std::cin >> m;

    std::vector<std::string> qs(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> qs[i];

    solve(ws, qs);

    return 0;
}