#include <iostream>
#include <string>
#include <vector>

unsigned solve(const std::vector<std::string>& m)
{
    const size_t n = m.size();

    std::vector<std::pair<size_t, size_t>> q;
    std::vector<std::vector<bool>> v(n, std::vector<bool>(n));

    const auto enqueue = [&](size_t r, size_t c) {
        if (r < n && c < n && m[r][c] == '.' && !v[r][c]) {
            q.emplace_back(r, c);
            v[r][c] = true;
        }
    };

    unsigned k = 0;
    {
        enqueue(0, 0);
        enqueue(n-1, n-1);

        for (size_t i = 0; i < q.size(); ++i) {
            const std::pair<size_t, size_t> x = q[i];

            if (x.first == 0 || m[x.first-1][x.second] == '#')
                ++k;
            if (x.first + 1 == n || m[x.first+1][x.second] == '#')
                ++k;
            if (x.second == 0 || m[x.first][x.second-1] == '#')
                ++k;
            if (x.second + 1 == n || m[x.first][x.second+1] == '#')
                ++k;

            enqueue(x.first - 1, x.second);
            enqueue(x.first, x.second + 1);
            enqueue(x.first + 1, x.second);
            enqueue(x.first, x.second - 1);
        }
    }
    return k - 4;
}

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<std::string> m(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> m[i];

    std::cout << solve(m) * 9 << '\n';

    return 0;
}
