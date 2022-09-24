#include <algorithm>
#include <iostream>
#include <vector>

size_t search(const std::vector<std::pair<int, int>>& s, size_t i, int x)
{
    const size_t n = s.size();

    size_t b = n;
    for ( ; i < n && s[i].first <= x; ++i) {
        if (b == n || s[i].second > s[b].second)
            b = i;
    }
    return b;
}

int main()
{
    int m;
    std::cin >> m;

    std::vector<std::pair<int, int>> s;
    while (true) {
        int l, r;
        std::cin >> l >> r;

        if (l == 0 && r == 0)
            break;

        if (l <= m && r >= 0)
            s.emplace_back(l, r);
    }

    const size_t n = s.size();

    std::sort(s.begin(), s.end());

    std::vector<size_t> p;
    for (int x = 0, i = 0; x < m && i < n; ++i) {
        i = search(s, i, x);
        if (i < n) {
            p.push_back(i);
            x = s[i].second;
        }
    }

    if (!p.empty() && s[p.back()].second >= m) {
        std::cout << p.size() << '\n';
        for (const size_t i : p) {
            std::cout << s[i].first << ' ' << s[i].second << '\n';
        }
    } else {
        std::cout << "No solution" << '\n';
    }

    return 0;
}
