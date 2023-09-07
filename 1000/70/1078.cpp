#include <algorithm>
#include <iostream>
#include <vector>

void print(const std::vector<std::pair<unsigned, size_t>>& v, size_t x, unsigned k, size_t n)
{
    if (x == n) {
        std::cout << k << '\n';
    } else {
        print(v, v[x].second, k + 1, n);

        std::cout << 1 + x << ' ';
    }
}

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<std::pair<int, int>> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i].first >> s[i].second;

    std::vector<size_t> p(n);
    for (size_t i = 0; i < n; ++i)
        p[i] = i;

    std::sort(p.begin(), p.end(), [&](size_t i, size_t j) {
        const unsigned di = s[i].second - s[i].first, dj = s[j].second - s[j].first;
        return di != dj ? di < dj : s[i].first < s[j].first;
    });

    std::vector<std::pair<unsigned, size_t>> v(n, std::make_pair(1, n));
    for (const size_t i : p) {
        for (const size_t j : p) {
            if (j == i)
                break;

            if (s[j].first <= s[i].first || s[j].second >= s[i].second)
                continue;

            if (v[i].first <= v[j].first) {
                v[i].first = v[j].first + 1;
                v[i].second = j;
            }
        }
    }

    size_t x = 0;
    for (size_t i = 1; i < n; ++i) {
        if (v[i].first > v[x].first)
            x = i;
    }

    print(v, x, 0, n);

    return 0;
}
