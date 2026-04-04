#include <iomanip>
#include <iostream>
#include <vector>

#include <cmath>

const double pi = acos(-1);

double F(const std::vector<unsigned>& a, size_t b, double x)
{
    double s = 0;
    for (size_t i = b; i < a.size(); ++i)
        s += asin(a[i] * x);

    return s;
}

template <typename Q>
double search(const std::vector<unsigned>& a, Q&& q)
{
    double lb = 0, ub = 1.0 / a[0];
    for (unsigned i = 0; i < 100; ++i) {
        const double mid = (lb + ub) / 2;
        (q(mid) ? lb : ub) = mid;
    }
    return (lb + ub) / 2;
}

double subarea(unsigned d, double r)
{
    return d * sqrt(1 - d * d * r * r);
}

double area(const std::vector<unsigned>& a, double r)
{
    double s = 0;
    for (const unsigned x : a)
        s += subarea(x, r);

    return s;
}

double solve(std::vector<unsigned>& a)
{
    unsigned s = 0;
    for (unsigned& x : a) {
        s += x;

        if (a[0] < x)
            std::swap(a[0], x);
    }

    if (a[0] >= s - a[0])
        return 0;

    double S = 0;
    if (F(a, 0, 1.0 / a[0]) >= pi) {
        const double r = search(a, [&](double x) { return F(a, 0, x) < pi; });
        S = area(a, r);
        S /= 4 * r;
    } else {
        const double r = search(a, [&](double x) { return F(a, 1, x) > asin(a[0] * x); });
        S = area(a, r);
        S -= 2 * subarea(a[0], r);
        S /= 4 * r;
    }
    return S;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::cout << std::fixed << std::setprecision(2) << solve(a) << '\n';

    return 0;
}
