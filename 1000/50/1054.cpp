#include <iostream>
#include <vector>

using integer = long long;

integer search(const std::vector<unsigned>& t, size_t x, unsigned u, unsigned v, unsigned w)
{
    if (x-- == 0)
        return 0;

    if (t[x] == u)
        return search(t, x, u, w, v);

    if (t[x] != v)
        return -1;

    const integer s = search(t, x, w, v, u);
    return s == -1 ? -1 : (1ull << x) + s;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> d(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> d[i];

    std::cout << search(d, n, 1, 2, 3) << '\n';

    return 0;
}
