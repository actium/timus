#include <iostream>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    unsigned s = 0, w = 0;
    for (size_t i = 0; i < n; ++i) {
        unsigned x;
        std::cin >> x;

        s += x;
        w = std::max(w, x);
    }

    std::cout << (2 * w <= s ? 1 : 2 * w - s) << ' ' << w << '\n';

    return 0;
}
