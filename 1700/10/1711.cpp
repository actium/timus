#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

void solve(const std::vector<std::array<std::string, 3>>& s, const std::vector<int>& p)
{
    const size_t n = s.size();

    std::vector<std::string> r(n);
    r[0] = s[p[0]-1].front();
    for (size_t i = 1; i < n; ++i) {
        const auto& v = s[p[i]-1];

        const auto it = std::upper_bound(v.cbegin(), v.cend(), r[i-1]);
        if (it == v.cend()) {
            std::cout << "IMPOSSIBLE" << '\n';
            return;
        }

        r[i] = *it;
    }

    for (const std::string& x : r)
        std::cout << x << '\n';
}

int main()
{
    int n;
    std::cin >> n;

    std::vector<std::array<std::string, 3>> s(n);
    for (int i = 0; i < n; ++i) {
        for (std::string& x : s[i])
            std::cin >> x;

        std::sort(s[i].begin(), s[i].end());
    }

    std::vector<int> p(n);
    for (int i = 0; i < n; ++i)
        std::cin >> p[i];

    solve(s, p);

    return 0;
}
