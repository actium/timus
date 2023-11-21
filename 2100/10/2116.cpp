#include <iostream>
#include <vector>

using integer = unsigned long long;

void paint(std::vector<std::vector<unsigned>>& c, size_t i, size_t j, unsigned a, unsigned b, unsigned k)
{
    if (i >= c.size() || j >= c.size() || c[i][j] != 0)
        return;

    c[i][j] = k;

    paint(c, i - a, j + b, a, b, k);
    paint(c, i - b, j + a, a, b, k);
    paint(c, i + b, j + a, a, b, k);
    paint(c, i + a, j + b, a, b, k);
    paint(c, i + a, j - b, a, b, k);
    paint(c, i + b, j - a, a, b, k);
    paint(c, i - b, j - a, a, b, k);
    paint(c, i - a, j - b, a, b, k);
}

integer solve(unsigned n, unsigned a, unsigned b)
{
    if (a == 0 && b == 0)
        return 1ull * n * n;

    n = std::min(n, 6u);

    unsigned k = 0;
    {
        std::vector<std::vector<unsigned>> c(n, std::vector<unsigned>(n));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (c[i][j] == 0)
                    paint(c, i, j, a, b, ++k);
            }
        }
    }
    return k;
}

int main()
{
    unsigned n, a, b;
    std::cin >> n >> a >> b;

    std::cout << solve(n, a, b) << '\n';

    return 0;
}
