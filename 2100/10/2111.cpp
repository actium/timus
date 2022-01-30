#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> d(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> d[i];

    std::sort(d.begin(), d.end(), std::greater<unsigned>());

    unsigned long long w = std::accumulate(d.cbegin(), d.cend(), 0ull), c = 0;
    for (size_t i = 0; i < n; ++i) {
        c += w * d[i];
        w -= d[i];
        c += w * d[i];
    }

    std::cout << c << '\n';

    return 0;
}
