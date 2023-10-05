#include <algorithm>
#include <iostream>
#include <vector>

unsigned solve(std::vector<std::pair<unsigned, unsigned>>& a)
{
    const size_t n = a.size();

    if (n == 0)
        return 0;

    std::sort(a.begin(), a.end());

    std::vector<unsigned> s(n, 1);
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (a[i].second > a[j].second)
                s[i] = std::max(s[i], s[j] + 1);
        }
    }

    return n - *std::max_element(s.begin(), s.end());
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t k;
    std::cin >> k;

    std::vector<std::pair<unsigned, unsigned>> a(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> a[i].first >> a[i].second;

    std::cout << solve(a) << '\n';

    return 0;
}
