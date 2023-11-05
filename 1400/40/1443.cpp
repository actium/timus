#include <cstdio>

using integer = unsigned long long;

unsigned solve(unsigned n, integer s, integer p)
{
    unsigned k = s / p * n;

    s %= p;
    if (s != 0) {
        const unsigned d = p / s;
        k += (n + d - 1) / d;
    }

    return k;
}

int main()
{
    unsigned n;
    scanf("%u", &n);

    double s, p;
    scanf("%lf %lf", &s, &p);

    const unsigned k = solve(n, s * 10000 + 0.5, p * 10000 + 0.5);
    printf("%u", k);

    return 0;
}
