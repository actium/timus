#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    unsigned k;
    std::cin >> k;

    const size_t q = n * m;

    std::vector<unsigned> h(q);
    for (size_t i = 0; i < q; ++i)
        std::cin >> h[i];

    std::sort(h.begin(), h.end());

    unsigned x = h[0];
    for (size_t i = 1; i < q; ++i) {
        const unsigned d = std::min<unsigned>((h[i] - x) * i, k);
        x += d / i;
        k -= d;
    }

    std::cout << x + k / q << '\n';

    return 0;
}
