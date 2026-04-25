#include <iostream>

bool leap(unsigned y)
{
    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
}

unsigned count_leap_years(unsigned ub)
{
    unsigned k = 0;
    for (unsigned i = 1; i <= ub; ++i)
        k += leap(i);

    return k;
}

unsigned month_length(unsigned m, bool leap)
{
    constexpr unsigned month_lengths[] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    return month_lengths[m] + (leap && m == 1);
}

unsigned counts[13][401];

void initialize_counts()
{
    const auto count = [](unsigned y) {
        const unsigned shift = (y-1) * 365 + count_leap_years(y-1);

        unsigned k = 0;
        for (unsigned m = 0, d = 1 + shift; m < 12; ++m) {
            k += (d % 7 == 0);
            d += month_length(m, leap(y));
        }
        return k;
    };

    for (unsigned y = 1; y <= 400; ++y) {
        const unsigned c = count(y);

        for (unsigned i = 1; i <= 3; ++i)
            counts[i][y] = counts[i][y-1] + (c == i);
    }
}


int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    initialize_counts();

    unsigned a, b;
    std::cin >> a >> b;

    const auto count = [](unsigned k, unsigned y) {
        return counts[k][400] * (y / 400) + counts[k][y % 400];
    };

    for (unsigned k = 0; k <= 12; ++k)
        std::cout << k << ": " << count(k, b) - count(k, a-1) << '\n';

    return 0;
}
