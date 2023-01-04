#include <algorithm>
#include <iostream>
#include <vector>

constexpr std::pair<size_t, size_t> p[][3] = {
    { {0, 0}, {0, 1}, {0, 2} },
    { {1, 0}, {1, 1}, {1, 2} },
    { {2, 0}, {2, 1}, {2, 2} },
    { {0, 0}, {1, 0}, {2, 0} },
    { {0, 1}, {1, 1}, {2, 1} },
    { {0, 2}, {1, 2}, {2, 2} },
    { {0, 0}, {1, 1}, {2, 2} },
    { {0, 2}, {1, 1}, {2, 0} }
};

bool check(const char b[3][3])
{
    for (const auto& q : p) {
        unsigned x = 0, o = 0;
        for (const std::pair<size_t, size_t>& c : q) {
            x += b[c.first][c.second] == 'X';
            o += b[c.first][c.second] == 'O';
        }
        if (x + o == 3 && x * o == 0)
            return true;
    }
    return false;
}

int solve(char b[3][3], char t)
{
    std::vector<int> r;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if (b[i][j] != '#')
                continue;

            b[i][j] = t;
            if (check(b)) {
                b[i][j] = '#';
                return 1;
            } else {
                r.push_back(solve(b, t ^ 'X' ^ 'O'));
            }
            b[i][j] = '#';
        }
    }
    return r.empty() ? 0 : -*std::min_element(r.begin(), r.end());
}

int main()
{
    char b[3][3];
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j)
            std::cin >> b[i][j];
    }

    constexpr const char* v[3] = { "Ouths win", "Draw", "Crosses win" };
    std::cout << v[solve(b, 'X') + 1] << '\n';

    return 0;
}
