#include <iostream>
#include <vector>

unsigned clamp(int v, unsigned b)
{
    return v < 0 ? 0 : std::min<unsigned>(v, b);
}

unsigned solve(const std::vector<unsigned>& a, unsigned l)
{
    const size_t n = a.size();

    const unsigned p = a[0], s = l - a[n-1];

    unsigned d = p + s;
    for (size_t i = 1; i < n; ++i) {
        const unsigned dx = a[i] - a[i-1];

        const unsigned d1 = clamp(dx - (l - a[i]), dx);
        const unsigned d2 = clamp(p - (a[i-1] - p), dx);
        const unsigned d3 = clamp(dx - a[i-1], dx);
        const unsigned d4 = clamp(s - (a[n-1] - a[i]), dx);

        d += clamp(std::max(d1, d2) + std::max(d3, d4), dx);
    }
    return d;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned l;
    std::cin >> l;

    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::cout << solve(a, l) << '\n';

    return 0;
}
