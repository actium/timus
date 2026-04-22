#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

unsigned count_triplets(std::vector<std::vector<unsigned>> f)
{
    unsigned k = 0;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 1; j < 10; ++j) {
            if (f[i][j] >= 3) {
                f[i][j] -= 3;
                ++k;
            }
            if (j < 8) {
                const unsigned c = std::min({ f[i][j], f[i][j+1], f[i][j+2] });
                f[i][j] -= c;
                f[i][j+1] -= c;
                f[i][j+2] -= c;
                k += c;
            }
        }
    }
    return k;
}

bool test_tsumo(const std::vector<std::string>& c)
{
    std::vector<std::vector<unsigned>> f(3, std::vector<unsigned>(10));
    for (size_t i = 0; i < 14; ++i) {
        ++f[c[i][1]-'a'][c[i][0]-'0'];
        ++f[c[i][1]-'a'][0];
    }

    std::sort(std::begin(f), std::end(f), [](const auto& lhs, const auto& rhs) {
        return lhs[0] % 3 > rhs[0] % 3;
    });

    if (f[0][0] % 3 != 2 || f[1][0] % 3 != 0)
        return false;

    for (unsigned x = 1; x <= 9; ++x) {
        if (f[0][x] < 2)
            continue;

        f[0][x] -= 2;

        if (count_triplets(f) == 4)
            return true;

        f[0][x] += 2;
    }
    return false;
}

std::string_view solve(std::vector<std::string>& c)
{
    if (test_tsumo(c))
        return "Tsumo";

    for (size_t i = 0; i < 14; ++i) {
        const std::string b = c[i];
        for (c[i][0] = '1'; c[i][0] <= '9'; ++c[i][0]) {
            for (c[i][1] = 'a'; c[i][1] <= 'c'; ++c[i][1]) {
                if (test_tsumo(c))
                    return "Tenpai";
            }
        }
        c[i] = b;
    }

    return "Noten";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> c(14);
    for (size_t i = 0; i < 14; ++i)
        std::cin >> c[i];

    std::cout << solve(c) << '\n';

    return 0;
}
