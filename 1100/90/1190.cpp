#include <iostream>
#include <string>
#include <vector>

const char* solve(const std::vector<unsigned>& p)
{
    unsigned lb = 1, s = 0;
    for (auto it = p.rbegin(); it != p.rend(); ++it) {
        if (*it != 0 && *it < lb)
            return "NO";

        if (*it > lb)
            lb = *it;

        s += lb;
        if (s > 10000)
            return "NO";
    }

    if (p[0] != 0) {
        unsigned ub = p[0], s = 0;
        for (unsigned x : p) {
            if (x != 0 && x < ub)
                ub = x;

            s += ub;
        }
        if (s < 10000)
            return "NO";
    }

    return "YES";
}

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> p(n);
    for (size_t i = 0; i < n; ++i) {
        std::string x;
        std::cin >> x;

        std::cin >> p[i];
        if (p[i] == 1)
            std::cin >> p[i];
    }

    std::cout << solve(p) << '\n';

    return 0;
}
