#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

unsigned solve(const std::vector<unsigned>& a)
{
    const size_t n = a.size();

    std::vector<size_t> p(n);
    for (size_t i = 0; i < n; ++i)
        p[i] = i;

    std::sort(p.begin(), p.end(), [&](size_t i, size_t j) {
        return a[i] < a[j];
    });

    unsigned d1 = 0, d2 = 0;
    for (int i = 0; i < n; ++i) {
        const int j = p[i];
        d1 = std::gcd(d1, abs(i - j));

        const int k = n - 1 - i;
        d2 = std::gcd(d2, abs(k - j));
    }

    if (d1 == 0)
        d1 = n;

    if (d2 == 0)
        d2 = n;

    return std::max(d1, d2) - 1;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::cout << solve(a) << '\n';

    return 0;
}
