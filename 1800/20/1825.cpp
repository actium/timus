#include <iostream>

#include <cmath>

const double pi = acos(-1);

double square(unsigned x)
{
    return x * x;
}

double solve(unsigned d, unsigned r1, unsigned R1, unsigned r2, unsigned R2)
{
    const auto area = [&](unsigned p, unsigned q) {
        if (d >= p + q)
            return 0.0;

        if (d <= std::max(p, q) - std::min(p, q))
            return pi * square(std::min(p, q));

        const auto u = square(d) + square(p) - square(q), v = square(d) + square(q) - square(p);
        const auto w = double(p + q + d) * (p + q - d) * (p - q + d) * (q - p + d);
        return square(p) * acos(u / (2.0 * d * p)) + square(q) * acos(v / (2.0 * d * q)) - sqrt(w) / 2.0;
    };

    return pi * (square(R1) - square(r1) + square(R2) - square(r2)) - area(R1, R2) + area(r1, R2) + area(r2, R1) - area(r1, r2);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned d;
    std::cin>> d;

    unsigned r1, R1, r2, R2;
    std::cin >> r1 >> R1 >> r2 >> R2;

    std::cout << std::fixed << solve(d, r1, R1, r2, R2) << '\n';

    return 0;
}
