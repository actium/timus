#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    size_t n, k;
    std::cin >> n >> k;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    const size_t rc = (n + k - 1) / k;
    for (size_t i = 0; i < rc; ++i) {
        for (size_t j = 0; j < k; ++j) {
            const size_t x = j * rc + i;
            if (x < n)
                std::cout << std::setw(4) << a[x];
        }
        std::cout << '\n';
    }

    return 0;
}
