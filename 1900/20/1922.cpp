#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<std::pair<unsigned, size_t>> h(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> h[i].first;
        h[i].second = i;
    }

    std::sort(h.begin(), h.end());

    h.emplace_back(~0u, n);   // sentinel

    std::vector<size_t> s;
    for (size_t i = 1; i <= n; ++i) {
        if (h[i-1].first <= i && h[i].first > i + 1)
            s.push_back(i);
    }

    std::cout << s.size() << '\n';
    for (const size_t k : s) {
        std::cout << k;
        for (size_t i = 0; i < k; ++i)
            std::cout << ' ' << h[i].second + 1;

        std::cout << '\n';
    }

    return 0;
}
