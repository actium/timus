#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using integer = unsigned long long;

integer solve(const std::vector<unsigned>& s, std::vector<unsigned>& p)
{
    const size_t n = s.size();

    unsigned g = 0;
    for (size_t i = 0; i < n; ++i)
        g = std::gcd(g, p[i]);

    integer tp = 0;
    for (size_t i = 0; i < n; ++i) {
        p[i] /= g;
        tp += p[i];
    }

    std::vector<size_t> c(n);
    for (size_t i = 0; i < n; ++i)
        c[i] = i;

    std::sort(c.begin(), c.end(), [&](size_t i, size_t j) {
        return 1ull * s[i] * p[j] < 1ull * s[j] * p[i];
    });

    size_t m = 0;
    for (integer cp = 0; 2 * cp <= tp; ++m)
        cp += p[c[m]];

    const auto count = [&](integer b) {
        integer k = 0;
        for (size_t i = 0; i < n; ++i) {
            const integer x = b * p[i];
            k += std::max<integer>(s[i], x) - std::min<integer>(s[i], x);
        }
        return k;
    };

    const integer b = s[c[m-1]] / p[c[m-1]];
    return b == 0 ? count(b+1) : std::min(count(b), count(b+1));
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i];

    std::vector<unsigned> p(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> p[i];

    std::cout << solve(s, p) << '\n';

    return 0;
}
