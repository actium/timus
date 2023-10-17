#include <iostream>

double a[400][400];
double b[400][400];

void initialize(unsigned ub)
{
    a[0][0] = 1;
    a[1][0] = 1;

    for (unsigned i = 0; i < ub; ++i) {
        b[0][i] = 1;
        b[1][i] = 1;
    }
}

void update(unsigned n, unsigned m, unsigned i, unsigned ub)
{
    double s = 0;
    for (unsigned j = 1; j < ub; ++j) {
        const double p = (a[m][j-1] * b[i][j-1] + a[i][j-1] * b[m][j-1] - a[m][j-1] * a[i][j-1]) / n;
        a[n][j] += p;
        s += p;
        b[n][j] += s;
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    initialize(n);

    for (unsigned k = 2; k < n - 1; ++k) {
        for (unsigned i = 0; i < k; ++i)
            update(k, k - 1 - i, i, n);
    }

    double d = 10;
    for (unsigned i = 0; i < n; ++i)
        d += a[n-2][i] * 10 * i;

    std::cout << std::fixed << d << '\n';

    return 0;
}
