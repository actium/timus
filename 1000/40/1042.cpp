#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<std::vector<unsigned>> v(n, std::vector<unsigned>(n + 1));
    for (unsigned i = 0; i < n; ++i) {
        int x;
        for (std::cin >> x; x != -1; std::cin >> x) {
            v[x-1][i] = 1;
            v[x-1][n] = 1;
        }
    }

    for (unsigned i = 0; i < n; ++i) {
        unsigned k = i;
        while (k < n && v[k][i] == 0)
            ++k;

        for (unsigned j = 0; j <= n; ++j)
            std::swap(v[k][j], v[i][j]);

        for (k = 0; k < n; ++k) {
            if (k == i || v[k][i] == 0)
                continue;

            for (unsigned j = i; j <= n; ++j)
                v[k][j] ^= v[i][j];
        }
    }

    for (unsigned i = 0; i < n; ++i) {
        if (v[i][n] == 1)
            std::cout << i + 1 << ' ';
    }

    return 0;
}