#include <iostream>
#include <vector>

bool solve(unsigned i, unsigned j, unsigned n, std::vector<std::pair<unsigned, unsigned>>& p)
{
    static bool v[8][8] = {};

    p.emplace_back(i, j);
    v[i][j] = true;

    if (p.size() == n * n)
        return true;

    constexpr int di[] = { -2, -1,  1,  2,  2,  1, -1, -2 };
    constexpr int dj[] = {  1,  2,  2,  1, -1, -2, -2, -1 };
    for (size_t k = 0; k < 8; ++k) {
        const unsigned r = i + di[k], c = j + dj[k];
        if (r >= n || c >= n || v[r][c])
            continue;

        if (solve(r, c, n, p))
            return true;
    }

    p.pop_back();
    v[i][j] = false;

    return false;
}

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<std::pair<unsigned, unsigned>> p;
    if (!solve(0, 0, n, p)) {
        std::cout << "IMPOSSIBLE" << '\n';
    } else {
        constexpr const char* t1 = "abcdefgh";
        for (const std::pair<unsigned, unsigned>& x : p)
            std::cout << t1[x.first] << char('1' + x.second) << '\n';
    }

    return 0;
}
