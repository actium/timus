#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    using segment_t = std::pair<int, int>;

    size_t n;
    std::cin >> n;

    std::vector<segment_t> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i].first >> s[i].second;

    std::sort(s.begin(), s.end());

    std::vector<segment_t> t;
    for (const segment_t& x : s) {
        if (!t.empty() && x.second <= t.back().second)
            t.pop_back();

        if (t.empty() || x.first >= t.back().second)
            t.push_back(x);
    }

    std::cout << t.size() << '\n';
    for (const segment_t& x : t)
        std::cout << x.first << ' ' << x.second << '\n';

    return 0;
}
