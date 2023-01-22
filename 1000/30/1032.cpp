#include <iostream>
#include <vector>

std::pair<size_t, size_t> solve(const std::vector<unsigned>& a)
{
    const size_t n = a.size();

    std::vector<size_t> r(n, n);
    unsigned s = 0;
    for (size_t i = 0; i < n; ++i) {
        s += a[i];

        const unsigned x = s % n;
        if (x == 0)
            return std::make_pair(0, i + 1);

        if (r[x] < n)
            return std::make_pair(r[x] + 1, i - r[x]);

        r[x] = i;
    }
    return std::make_pair(n, 0);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    const std::pair<size_t, size_t> r = solve(a);
    std::cout << r.second << '\n';
    for (size_t i = 0; i < r.second; ++i)
        std::cout << a[r.first + i] << '\n';

    return 0;
}
