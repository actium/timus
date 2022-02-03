#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<std::vector<unsigned>> d(5, std::vector<unsigned>(5));
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j)
            std::cin >> d[i][j];
    }

    const auto f = [&d](const std::vector<size_t>& p) {
        return d[0][p[0]] + d[p[0]][p[1]] + d[p[1]][p[2]] + d[p[2]][4];
    };

    std::vector<size_t> p = { 1, 2, 3 }, b = p;
    do {
        if (p.back() != 2 && f(p) < f(b))
            b = p;
    } while (std::next_permutation(p.begin(), p.end()));

    std::cout << f(b) << '\n';
    std::cout << 1 << ' ' << 1+b[0] << ' ' << 1+b[1] << ' ' << 1+b[2] << ' ' << 5 << '\n';

    return 0;
}
