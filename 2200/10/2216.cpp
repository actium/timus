#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    size_t k;
    std::cin >> k;

    std::vector<int> da(1+n+1);
    for (size_t i = 0; i < k; ++i) {
        unsigned l, r;
        std::cin >> l >> r;

        if (l < r) {
            ++da[l];
            --da[r+1];
        }
    }

    int v = k;
    for (unsigned i = 1; i <= n; ++i) {
        da[i] += da[i-1];
        v = std::min(v, da[i]);
    }

    std::cout << (v != 0 ? v : -1) << '\n';

    return 0;
}
