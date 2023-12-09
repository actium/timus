#include <algorithm>
#include <iostream>
#include <vector>

#include <cmath>

constexpr double epsilon = 1e-8;

struct Object {
    double x;
    double y;
    double z;

    double dx;
    double dy;
    double dz;
};

struct Alarm {
    size_t u;
    size_t v;
    double t;
};

void solve(const std::vector<Object>& p, double d)
{
    const size_t n = p.size();

    const auto dot = [](double dx, double dy, double dz) {
        return dx * dx + dy * dy + dz * dz;
    };

    std::vector<Alarm> alarms;
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            const double dx = p[i].x - p[j].x, vx = p[i].dx - p[j].dx;
            const double dy = p[i].y - p[j].y, vy = p[i].dy - p[j].dy;
            const double dz = p[i].z - p[j].z, vz = p[i].dz - p[j].dz;

            const double w = dot(vx, vy, vz), v = vx * dx + vy * dy + vz * dz, u = dot(dx, dy, dz) - d * d;
            if (v * v + epsilon > u * w) {
                const double t = -v / sqrt(w) - sqrt(std::max(v * v / w - u, 0.0));
                if (t > 0)
                    alarms.push_back({ 1 + j, 1 + i, t / sqrt(w) });
            }
        }
    }

    if (alarms.empty()) {
        std::cout << "OK" << '\n';
    } else {
        const auto x = std::min_element(alarms.begin(), alarms.end(), [](const Alarm& lhs, const Alarm& rhs) {
            return lhs.t < rhs.t;
        });

        std::cout << "ALARM!" << '\n';
        std::cout << std::fixed << x->t << ' ' << x->u << ' ' << x->v << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    double d;
    std::cin >> d;

    std::vector<Object> p(n);
    for (Object& q : p)
        std::cin >> q.x >> q.y >> q.z >> q.dx >> q.dy >> q.dz;

    solve(p, d);

    return 0;
}
