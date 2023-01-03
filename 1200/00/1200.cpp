#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    double a, b;
    std::cin >> a >> b;

    unsigned k;
    std::cin >> k;

    std::vector<double> va(1 + k), vb(1 + k);
    for (unsigned i = 0; i <= k; ++i) {
        const auto d = 1ull * i * i;
        va[i] = i * a - d;
        vb[i] = i * b - d;
    }

    std::vector<unsigned> ma(1 + k), mb(1 + k);
    for (unsigned i = 1; i <= k; ++i) {
        ma[i] = (va[i] > va[ma[i-1]] ? i : ma[i-1]);
        mb[i] = (vb[i] > vb[mb[i-1]] ? i : mb[i-1]);
    }

    unsigned x = 0, y = 0;
    for (unsigned i = 0; i <= k; ++i) {
        const unsigned j = mb[k-i];
        if (va[i] + vb[j] > va[x] + vb[y]) {
            x = i;
            y = j;
        }
    }

    std::cout << std::fixed << std::setprecision(2) << va[x] + vb[y] << '\n';
    std::cout << x << ' ' << y << '\n';

    return 0;
}
