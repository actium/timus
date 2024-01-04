#include <iostream>
#include <vector>

int main()
{
    unsigned n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::pair<unsigned, unsigned>> p(1 + n);
    for (unsigned i = 1; i <= n; ++i) {
        for (unsigned j = i - 1; j + k >= i; --j) {
            if (~j == 0) {
                p[i] = std::max<std::pair<unsigned, unsigned>>(p[i], std::make_pair(m, 0));
                break;
            }

            const std::pair<unsigned, unsigned> u = { i - j + p[j].second, p[j].first };
            if (u.first > p[i].first || u.first == p[i].first && u.second < p[i].second)
                p[i] = u;
        }
    }

    std::cout << p[n].first << ' ' << p[n].second << '\n';

    return 0;
}
