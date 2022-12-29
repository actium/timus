#include <algorithm>
#include <iostream>
#include <vector>

const char* solve(std::vector<std::vector<unsigned>>& a)
{
    const size_t n = a.size();

    for (const std::vector<unsigned>& v : a) {
        if (!std::is_sorted(v.begin(), v.end()))
            return "NO";
    }

    std::sort(a.begin(), a.end());

    for (size_t i = 1; i < n; ++i) {
        if (a[i].front() < a[i-1].back())
            return "NO";
    }

    return "YES";
}

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<std::vector<unsigned>> a(n);
    for (size_t i = 0; i < n; ++i) {
        size_t k;
        std::cin >> k;

        a[i].resize(k);
        for (size_t j = 0; j < k; ++j)
            std::cin >> a[i][j];
    }

    std::cout << solve(a) << '\n';

    return 0;
}
