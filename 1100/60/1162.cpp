#include <iostream>
#include <vector>

struct ExchangePoint {
    unsigned a;
    unsigned b;

    double rab;
    double cab;

    double rba;
    double cba;
};

std::istream& operator >>(std::istream& input, ExchangePoint& p)
{
    return input >> p.a >> p.b >> p.rab >> p.cab >> p.rba >> p.cba;
}

const char* solve(unsigned n, const std::vector<ExchangePoint>& p, unsigned s, double v)
{
    std::vector<double> d(1 + n);
    d[s] = v;
    for (size_t i = 0; i < n; ++i) {
        for (const ExchangePoint& x : p) {
            const double wab = (d[x.a] - x.cab) * x.rab;
            if (wab > d[x.b])
                d[x.b] = wab;

            const double wba = (d[x.b] - x.cba) * x.rba;
            if (wba > d[x.a])
                d[x.a] = wba;
        }
    }

    for (const ExchangePoint& x : p) {
        const double wab = (d[x.a] - x.cab) * x.rab;
        if (wab > d[x.b])
            return "YES";

        const double wba = (d[x.b] - x.cba) * x.rba;
        if (wba > d[x.a])
            return "YES";
    }

    return "NO";
}

int main()
{
    unsigned n, m, s;
    std::cin >> n >> m >> s;

    double v;
    std::cin >> v;

    std::vector<ExchangePoint> p(m);
    for (unsigned i = 0; i < m; ++i)
        std::cin >> p[i];

    std::cout << solve(n, p, s, v) << '\n';

    return 0;
}
