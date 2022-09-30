#include <iostream>

struct State {
    uint8_t k = 101;
    uint8_t d;
};

State t[1+900][1+8100];

void initialize()
{
    t[0][0].k = 0;
    t[0][0].d = 0;

    for (unsigned s1 = 0; s1 < 900; ++s1) {
        for (unsigned s2 = s1; s2 < 8100; ++s2) {
            if (t[s1][s2].k >= 100)
                continue;

            for (unsigned d = 1; d <= 9; ++d) {
                const unsigned u = s1 + d, v = s2 + d * d;
                if (u > 900 || v > 8100)
                    break;

                if (t[s1][s2].k + 1 > t[u][v].k)
                    continue;

                if (t[s1][s2].k + 1 < t[u][v].k || d < t[u][v].d) {
                    t[u][v].k = t[s1][s2].k + 1;
                    t[u][v].d = d;
                }
            }
        }
    }
}

void solve(unsigned s1, unsigned s2)
{
    if (s1 <= 900 && s2 <= 8100 && t[s1][s2].k <= 100) {
        for (unsigned d = t[s1][s2].d; d != 0; s1 -= d, s2 -= d * d, d = t[s1][s2].d)
            std::cout << char('0' + d);
    } else {
        std::cout << "No solution";
    }
    std::cout << '\n';
}

int main()
{
    initialize();

    unsigned t;
    for (std::cin >> t; t != 0; --t) {
        unsigned s1, s2;
        std::cin >> s1 >> s2;

        solve(s1, s2);
    }

    return 0;
}
