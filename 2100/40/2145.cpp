#include <algorithm>
#include <iostream>
#include <vector>

unsigned solve(std::vector<unsigned>& a, std::vector<unsigned>& b, unsigned p)
{
    const size_t n = a.size();

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    unsigned long long q = 1;
    for (size_t i = 0; i < n; ++i) {
        const size_t j = std::upper_bound(b.begin(), b.end(), a[i]) - b.begin();
        if (j <= i)
            return 0;

        q *= j - i;
        q %= p;
    }
    return q;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::vector<unsigned> b(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> b[i];

    unsigned p;
    std::cin >> p;

    std::cout << solve(a, b, p) << '\n';

    return 0;
}
