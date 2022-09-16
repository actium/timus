#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    const size_t k = std::min(n, m);

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::vector<unsigned> b(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> b[i];

    std::sort(a.begin(), a.end(), std::greater<unsigned>());
    std::partial_sum(a.begin(), a.end(), a.begin());

    std::sort(b.begin(), b.end(), std::greater<unsigned>());
    std::partial_sum(b.begin(), b.end(), b.begin());

    unsigned r = a.back();
    for (size_t i = 0; i < k; ++i) {
        const unsigned s = (a.back() - a[i]) + (b.back() - b[i]) * (i + 1);
        if (s < r)
            r = s;
    }

    std::cout << r << '\n';

    return 0;
}
