#include <algorithm>
#include <iostream>
#include <vector>

const char* solve(unsigned n, std::vector<unsigned>& a)
{
    const size_t m = a.size();
    if (m == 1)
        return "YES";

    std::sort(a.begin(), a.end());

    unsigned x = 0;
    for (size_t i = 0; i < m; ++i) {
        if (a[i] < x)
            return "NO";

        if (a[i] > x)
            x = a[i];
        else
            x = a[i] + 1;
    }

    return x > n ? "NO" : "YES";
}

int main()
{
    unsigned n;
    std::cin >> n;

    size_t m;
    std::cin >> m;

    std::vector<unsigned> a(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> a[i];

    std::cout << solve(n, a) << '\n';

    return 0;
}
