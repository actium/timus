#include <iostream>

int main()
{
    unsigned s[11][11] = { 1 };
    for (unsigned n = 0; n < 10; ++n) {
        for (unsigned k = 1; k < 11; ++k)
            s[n+1][k] = k * s[n][k] + s[n][k-1];
    }

    unsigned f[11] = { 1 };
    for (unsigned i = 1; i < 11; ++i)
        f[i] = f[i-1] * i;

    int x;
    for (std::cin >> x; x != -1; std::cin >> x) {
        unsigned r = 0;
        for (unsigned i = 1; i <= x; ++i)
            r += s[x][i] * f[i];

        std::cout << r << '\n';
    }

    return 0;
}
