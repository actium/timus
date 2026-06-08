#include <iostream>
#include <vector>

#include <cassert>

struct Vector {
    int dx = 0;
    int dy = 0;

    constexpr Vector() noexcept = default;

    constexpr Vector(int dx, int dy) noexcept
        : dx(dx)
        , dy(dy)
    {}
};

constexpr Vector operator +(const Vector& lhs, const Vector& rhs) noexcept
{
    return Vector(lhs.dx + rhs.dx, lhs.dy + rhs.dy);
}

constexpr Vector operator *(const Vector& lhs, int rhs) noexcept
{
    return Vector(lhs.dx * rhs, lhs.dy * rhs);
}

constexpr inline int dot_product(const Vector& lhs, const Vector& rhs) noexcept
{
    return lhs.dx * rhs.dx + lhs.dy * rhs.dy;
}

struct Node {
    size_t parents[2];
    int sign = 1;
};

std::string solve(std::vector<Vector>& vs, unsigned r)
{
    const size_t n = vs.size();

    if (n == 1)
        return "+";

    std::vector<Node> nodes(n);
    for (size_t i = 0; i < n; ++i)
        nodes[i] = {{ i, i }};

    std::vector<size_t> q(n);
    for (size_t i = 0; i < n; ++i)
        q[i] = i;

    const auto check_combo = [&](size_t i, size_t j, size_t k, unsigned factor = 1) {
        for (int x : { 1, -1 }) {
            const auto v = vs[i] + vs[j] * x;
            if (static_cast<unsigned>(dot_product(v, v)) <= factor * r * r) {
                vs.push_back(v);
                nodes.push_back({{ i, j }});
                nodes[j].sign *= x;
                q.push_back(nodes.size() - 1);
                q.push_back(k);
                return true;
            }
        }
        return false;
    };

    while (q.size() > 2) {
        size_t s[3];
        for (size_t i = 0; i < 3; ++i) {
            s[i] = q.back();
            q.pop_back();
        }

        check_combo(s[0], s[1], s[2]) || check_combo(s[1], s[2], s[0]) || check_combo(s[2], s[0], s[1]);
    }

    assert(q.size() == 2);

    check_combo(q[0], q[1], nodes.size(), 2);

    std::string s(n, ',');
    for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
        if (it->parents[0] != it->parents[1]) {
            nodes[it->parents[0]].sign *= it->sign;
            nodes[it->parents[1]].sign *= it->sign;
        } else {
            s[it->parents[0]] += it->sign;
        }
    }
    return s;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    unsigned r;
    std::cin >> r;

    std::vector<Vector> vs(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> vs[i].dx >> vs[i].dy;

    std::cout << "YES" << '\n';
    std::cout << solve(vs, r) << '\n';

    return 0;
}
