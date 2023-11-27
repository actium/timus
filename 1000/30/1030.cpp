#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <cmath>

const double pi = acos(-1);

double parse(const char* it)
{
    unsigned d = 0;
    while (*it != '^')
        d = d * 10 + (*it++ - '0');

    unsigned m = 0;
    while (*++it != '\'')
        m = m * 10 + (*it - '0');

    unsigned s = 0;
    while (*++it != '"')
        s = s * 10 + (*it - '0');

    const double v = (d * 3600 + m * 60 + s) / 3600.0;
    return *(it + 2) == 'N' || *(it + 2) == 'E' ? v : -v;
}

void solve(const std::vector<std::string>& s)
{
    const size_t n = s.size();

    for (size_t i = 0; i < n; i += 8) {
        const double d[] = {
            parse(s[i+3].data()),
            parse(s[i+4].data() + 4),
            parse(s[i+6].data()),
            parse(s[i+7].data() + 4),
        };

        const double p = (d[2] - d[0]) * pi / 180, q = (d[3] - d[1]) * pi / 180;
        const double u = d[0] * pi / 180, v = d[2] * pi / 180;

        const double a = sin(p / 2) * sin(p / 2) + cos(u) * cos(v) * sin(q / 2) * sin(q / 2);
        const double distance = 6875 * atan2(sqrt(a), sqrt(1 - a));

        std::cout << "The distance to the iceberg: " << std::fixed << std::setprecision(2) << distance << " miles.\n";

        if (distance * 100 + 0.5 < 10000)
            std::cout << "DANGER!\n";
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> s;
    for (std::string x; std::getline(std::cin, x); s.push_back(x));
    s.pop_back();

    solve(s);

    return 0;
}
