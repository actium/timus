#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<size_t> p(n);
    for (size_t i = 0; i < n; ++i) {
        unsigned x;
        std::cin >> x;

        p[x-1] = i;
    }

    for (size_t i = 0; i < n; ++i) {
        unsigned k1 = 0, k2 = 0;
        for (size_t j = 0; j < n; ++j) {
            if (j < i && p[j] > p[i])
                ++k1;

            if (j > i && p[j] < p[i])
                ++k2;
        }
        std::cout << k2 + 1 << ' ' << n - k1 << '\n';
    }

    return 0;
}
