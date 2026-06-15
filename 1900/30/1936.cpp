#include <iostream>

#include <cmath>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    double e[101] = {};
    for (unsigned i = 2; i <= n; ++i) {
        double s = 0, b = 1;
        for (unsigned k = 1; k < i; ++k) {
            b = b * (i - k + 1) / k;
            s += b * e[k];
        }

        e[i] = (std::pow(3, i-1) + s) / (std::pow(2, i) - 2);
    }

    std::cout << std::fixed << e[n] << '\n';

    return 0;
}
