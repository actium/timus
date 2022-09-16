#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<int> x(n), y(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> x[i] >> y[i];

    std::vector<size_t> p(n);
    for (size_t i = 0; i < n; ++i)
        p[i] = i;

    std::sort(p.begin(), p.end(), [&](size_t i, size_t j) {
        if (x[i] == x[j])
            return y[i] < y[j];

        return x[i] < x[j];
    });

    for (size_t i = 1; i < n; i += 2)
        std::cout << 1+p[i-1] << ' ' << 1+p[i] << '\n';

    return 0;
}
