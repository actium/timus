#include <iomanip>
#include <iostream>

#include <cmath>

using vector_t = std::pair<double, double>;

template <typename T, typename U>
std::istream& operator >>(std::istream& input, std::pair<T, U>& v)
{
    return input >> v.first >> v.second;
}

double dot_product(const vector_t& v, const vector_t& w)
{
    return v.first * w.first + v.second * w.second;
}

double min_distance(const vector_t& v, const vector_t& w, const vector_t& p)
{
    const double dx = w.first - v.first, dy = w.second - v.second;
    const double l2 = dx * dx + dy * dy;
    if (l2 == 0)
        return std::hypot(p.first - v.first, p.second - v.second);

    const vector_t a = { p.first - v.first, p.second - v.second };
    const vector_t b = { w.first - v.first, w.second - v.second };

    const double t = std::max(0.0, std::min(1.0, dot_product(a, b) / l2));
    const vector_t pr = { v.first + t * b.first, v.second + t * b.second };
    return std::hypot(p.first - pr.first, p.second - pr.second);
}

double max_distance(const vector_t& v, const vector_t& w, const vector_t& p)
{
    const vector_t a = { p.first - v.first, p.second - v.second };
    const vector_t b = { p.first - w.first, p.second - w.second };

    return std::max(std::hypot(a.first, a.second), std::hypot(b.first, b.second));
}

int main()
{
    std::pair<int, int> a, b, c;
    std::cin >> a >> b >> c;

    unsigned l;
    std::cin >> l;

    const double d1 = min_distance(a, b, c);
    const double d2 = max_distance(a, b, c);

    std::cout << std::fixed << std::setprecision(2) << std::max(d1 - l, 0.0) << '\n';
    std::cout << std::fixed << std::setprecision(2) << std::max(d2 - l, 0.0) << '\n';

    return 0;
}
