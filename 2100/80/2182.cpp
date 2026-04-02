#include <iostream>
#include <vector>

using integer = unsigned long long;

integer C[61][61];

void initialize()
{
    for (unsigned i = 0; i <= 60; ++i) {
        C[i][0] = 1;

        for (unsigned j = 1; j < i; ++j)
            C[i][j] = C[i-1][j-1] + C[i-1][j];

        C[i][i] = 1;
    }
}

void contribute(std::vector<integer>& c, unsigned i, integer d)
{
    c[i] += d;

    const unsigned k = __builtin_popcount(i);
    if (k != i)
        contribute(c, k, d);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    initialize();

    unsigned n;
    std::cin >> n;

    std::vector<integer> c(1+n);
    c[1] = n - 1;
    for (unsigned k = n; k != 1; --k)
        contribute(c, k, C[n][k]);

    unsigned q;
    std::cin >> q;

    for (unsigned i = 1; i <= q; ++i) {
        integer a;
        std::cin >> a;

        std::cout << 1 + (a > n ? 0 : c[a]) << " \n"[i==q];
    }

    return 0;
}
