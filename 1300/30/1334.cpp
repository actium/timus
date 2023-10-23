#include <iostream>

unsigned solve()
{
    unsigned b[8][8] = {}, t = 0;

    const auto check = [&] {
        for (size_t i = 0; i < 8; ++i) {
            for (size_t j = 0; j < 8; ++j) {
                if (i < 6 && j < 6 && b[i][j] + b[i+1][j+1] + b[i+2][j+2] == 4 && b[i+1][j+1] != 0)
                    return true;
                if (i < 6 && j > 1 && b[i][j] + b[i+1][j-1] + b[i+2][j-2] == 4 && b[i+1][j-1] != 0)
                    return true;
                if (i > 1 && j < 6 && b[i][j] + b[i-1][j+1] + b[i-2][j+2] == 4 && b[i-1][j+1] != 0)
                    return true;
                if (i > 1 && j > 1 && b[i][j] + b[i-1][j-1] + b[i-2][j-2] == 4 && b[i-1][j-1] != 0)
                    return true;
            }
        }
        return false;
    };

    for (unsigned t = 1; t <= 32; ++t) {
        char p, q;
        std::cin >> p >> q;

        const size_t r = p - 'a', c = q - '1';
        b[r][c] = (t % 2 == 1 ? 1 : 3);

        if (check())
            return t;
    }

    return 0;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    const unsigned t = solve();
    if (t != 0)
        std::cout << t << '\n';
    else
        std::cout << "Draw" << '\n';

    return 0;
}