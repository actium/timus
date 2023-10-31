#include <iomanip>
#include <iostream>

struct Vector {
    double dx;
    double dy;
};

std::istream& operator >>(std::istream& input, Vector& v)
{
    return input >> v.dx >> v.dy;
}

std::ostream& operator <<(std::ostream& output, const Vector& v)
{
    return output << std::fixed << std::setprecision(7) << v.dx << ' ' << v.dy;
}

Vector operator +(const Vector& lhs, const Vector& rhs)
{
    return { lhs.dx + rhs.dx, lhs.dy + rhs.dy };
}

Vector operator -(const Vector& lhs, const Vector& rhs)
{
    return { lhs.dx - rhs.dx, lhs.dy - rhs.dy };
}

double dot_product(const Vector& a, const Vector& b)
{
    return a.dx * b.dx + a.dy * b.dy;
}

double cross_product(const Vector& a, const Vector& b)
{
    return a.dx * b.dy - a.dy * b.dx;
}

Vector projection(const Vector& u, const Vector& v)
{
    const double d1 = dot_product(u, v), d2 = dot_product(v, v);
    return { v.dx * d1 / d2, v.dy * d1 / d2 };
}

bool check(const Vector& a, const Vector& b, const Vector& c, const Vector& x)
{
    return cross_product(x - b, a - b) * cross_product(c - b, a - b) < 1e-10
        || std::abs((c - x).dx) < 1e-10 && std::abs((c - x).dy) < 1e-10;
}

int main()
{
    Vector a, b, c;
    std::cin >> a >> b >> c;

    const Vector p = a + projection(b - a, c - a), d = c - p, x = c - (d + d);
    if (check(a, b, c, x)) {
        std::cout << "YES" << '\n';
    } else {
        std::cout << "NO" << '\n';

        std::cout << a << '\n';
        std::cout << b << '\n';
        std::cout << x << '\n';
    }

    return 0;
}
