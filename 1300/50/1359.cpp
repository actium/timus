#include <iostream>
#include <vector>

#include <cmath>

const double oo = 1e18;

struct Candidate {
    double t;
    double v;

    bool is_dominated_by(const Candidate& c) const
    {
        return c.t <= t && c.v >= v;
    }
};

double solve(unsigned h, unsigned d)
{
    std::vector<std::vector<std::vector<Candidate>>> cs(1+h, std::vector<std::vector<Candidate>>(1+d));

    const auto enqueue = [&](unsigned r, unsigned c, double t, double v) {
        const Candidate x = { t, v };
        for (size_t i = 0; i < cs[r][c].size(); ++i) {
            if (x.is_dominated_by(cs[r][c][i]))
                return;

            if (cs[r][c][i].is_dominated_by(x)) {
                cs[r][c][i--] = cs[r][c].back();
                cs[r][c].pop_back();
            }
        }

        cs[r][c].push_back(x);
    };

    enqueue(h, 0, 0, 0);

    for (unsigned r = h; r > 0; --r) {
        for (unsigned c = 0; c <= d; ++c) {
            for (const auto& q : cs[r][c]) {
                for (unsigned y = 0; y < r; ++y) {
                    for (unsigned x = c; x <= d; ++x) {
                        const auto s = std::hypot(r - y, x - c);
                        const auto a = 10 * (r - y) / s;
                        const auto v = std::sqrt(q.v * q.v + 2 * a * s);
                        enqueue(y, x, q.t + (v - q.v) / a, v);
                    }
                }
            }
        }
    }

    double t = oo;
    for (const auto& c : cs[0][d])
        t = std::min(t, c.t);

    return t;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, m;
    std::cin >> n >> m;

    std::cout << std::fixed << solve(m, n) << '\n';

    return 0;
}
