#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<int> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    const double p = (n - 1) / 2.0;
    const double q = (n - 1) * (2 * n - 1) / 6.0;

    long long s[2] = {};
    for (int i = 0; i < n; ++i) {
        s[0] += a[i] * i;
        s[1] += a[i];
    }

    const double d = (s[0] - s[1] * p) / (q - p * p);
    const double b = s[1] - d * p;

    std::cout << std::fixed << b / n << ' ' << d / n << '\n';

    return 0;
}
