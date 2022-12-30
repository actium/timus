#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::string> b(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> b[i];

    std::vector<std::vector<unsigned>> f(n, std::vector<unsigned>(m));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            std::cin >> f[i][j];
    }

    std::vector<unsigned> r(n), c(m);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            r[i] += f[i][j];
            c[j] += f[i][j];
        }
    }

    const auto check = [](unsigned x) {
        unsigned i = 1;
        while (i * i < x)
            ++i;

        return i * i == x;
    };

    std::vector<std::pair<unsigned, unsigned>> d;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            if (check(i * i + j * j))
                d.emplace_back(i, j);
        }
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            unsigned p = r[i] + c[j] + f[i][j];
            for (const std::pair<unsigned, unsigned>& q : d) {
                if (i >= q.first && j >= q.second)
                    p += f[i-q.first][j-q.second];
                if (i + q.first < n && j >= q.second)
                    p += f[i+q.first][j-q.second];
                if (i >= q.first && j + q.second < m)
                    p += f[i-q.first][j+q.second];
                if (i + q.first < n && j + q.second < m)
                    p += f[i+q.first][j+q.second];
            }

            if (p % 2 == 1)
                b[i][j] ^= 'W' ^ 'B';
        }
        std::cout << b[i] << '\n';
    }

    return 0;
}
