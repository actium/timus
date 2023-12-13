#include <cstdio>
#include <cstdlib>

int solve(unsigned t1, unsigned t2, unsigned t3, unsigned t4)
{
    for (int d = -5; d <= 5; ++d) {
        const unsigned dt1 = (t2 - d * 60 - t1 + 1440) % 1440;
        if (dt1 > 6 * 60)
            continue;

        const unsigned dt2 = (t4 + d * 60 - t3 + 1440) % 1440;
        if (dt2 > 6 * 60)
            continue;

        if (abs(dt1 - dt2) <= 10)
            return d;
    }

    return 0;
}

int main()
{
    unsigned h1, m1, h2, m2;
    scanf("%02u.%02u %02u.%02u", &h1, &m1, &h2, &m2);

    unsigned h3, m3, h4, m4;
    scanf("%02u.%02u %02u.%02u", &h3, &m3, &h4, &m4);

    const int d = solve(h1 * 60 + m1, h2 * 60 + m2, h3 * 60 + m3, h4 * 60 + m4);
    printf("%u", abs(d));

    return 0;
}
