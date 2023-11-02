#include <iostream>
#include <string>
#include <vector>

constexpr const char* t[10][3] = {
    { "._.", "|.|", "|_|" },
    { "...", "..|", "..|" },
    { "._.", "._|", "|_." },
    { "._.", "._|", "._|" },
    { "...", "|_|", "..|" },
    { "._.", "|_.", "._|" },
    { "._.", "|_.", "|_|" },
    { "._.", "..|", "..|" },
    { "._.", "|_|", "|_|" },
    { "._.", "|_|", "._|" },
};

constexpr unsigned b[4] = { 5, 9, 5, 9 };
constexpr size_t p[4] = { 0, 4, 10, 14 };

bool check(const std::vector<std::string>& s, size_t r, size_t c, unsigned x)
{
    for (size_t j = 0; j < 3; ++j) {
        for (size_t k = 0; k < 3; ++k) {
            if (s[r+j][c+k] != t[x][j][k] && s[r+j][c+k] != '.')
                return false;
        }
    }
    return true;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::string> s(n * 3);
    for (std::string& x : s)
        std::cin >> x;

    int d[4] = { 5, 9, 5, 9 };
    for (size_t i = 0; i < n; ++i) {
        for (int j = 3; j >= 0; --j) {
            int x = d[j];
            while (x >= 0 && !check(s, i * 3, p[j], x))
                --x;

            if (x != -1 && x == d[j])
                continue;

            d[j] = x;

            if (x < 0)
                --d[--j];

            for (++j; j < 4; ++j)
                d[j] = b[j];
        }

        std::cout << d[0] << d[1] << ':' << d[2] << d[3]-- << '\n';
    }

    return 0;
}
