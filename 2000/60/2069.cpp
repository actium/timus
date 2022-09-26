#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    std::vector<unsigned> v(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> v[i];

    std::vector<unsigned> h(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> h[i];

    const unsigned c1 = std::min(v.front(), h.back());
    const unsigned c2 = std::min(h.front(), v.back());

    const unsigned c3 = std::min({ h.front(), h.back(), *std::max_element(v.cbegin(), v.cend()) });
    const unsigned c4 = std::min({ v.front(), v.back(), *std::max_element(h.cbegin(), h.cend()) });

    std::cout << std::max({ c1, c2, c3, c4 }) << '\n';

    return 0;
}
