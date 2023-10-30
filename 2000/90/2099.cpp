#include <iostream>

using integer = long long;

struct Vector {
    integer dx;
    integer dy;
    integer dz;
};

std::istream& operator >>(std::istream& input, Vector& v)
{
    return input >> v.dx >> v.dy >> v.dz;
}

Vector operator -(const Vector& lhs, const Vector& rhs)
{
    return { lhs.dx - rhs.dx, lhs.dy - rhs.dy, lhs.dz - rhs.dz };
}

integer dot_product(const Vector& a, const Vector& b)
{
    return a.dx * b.dx + a.dy * b.dy + a.dz * b.dz;
}

Vector cross_product(const Vector& a, const Vector& b)
{
    return { a.dy * b.dz - a.dz * b.dy, a.dz * b.dx - a.dx * b.dz, a.dx * b.dy - a.dy * b.dx };
}

integer triple_product(const Vector& a, const Vector& b, const Vector& c)
{
    return dot_product(a, cross_product(b, c));
}

bool solve(const Vector& a, const Vector& b, const Vector& c, const Vector& d)
{
    return dot_product(b - a, d - c) == 0
        && triple_product(b - a, c - b, d - c) == 0
        && dot_product(b - a, c - b) >= 0
        && dot_product(d - c, c - b) >= 0
        && dot_product(d - c, d - b) >= dot_product(d - c, c - b);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    Vector a, b, c, d;
    std::cin >> a >> b >> c >> d;

    std::cout << (solve(a, b, c, d) ? "Valid" : "Invalid") << '\n';

    return 0;
}
