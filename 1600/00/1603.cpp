#include <array>
#include <iostream>

bool search(std::array<std::array<char, 4>, 4>& t, size_t i, size_t j, const std::string& s, size_t p)
{
    if (p == s.length())
        return true;

    if (t[i][j] != s[p])
        return false;

    const char c = t[i][j];
    t[i][j] = '*';

    const bool v = (i > 0 && search(t, i-1, j, s, p+1))
                || (i < 3 && search(t, i+1, j, s, p+1))
                || (j > 0 && search(t, i, j-1, s, p+1))
                || (j < 3 && search(t, i, j+1, s, p+1));

    t[i][j] = c;
    return v;
}

const char* solve(std::array<std::array<char, 4>, 4>& t, const std::string& s)
{
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            if (search(t, i, j, s, 0))
                return "YES";
        }
    }
    return "NO";
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::array<std::array<char, 4>, 4> t;
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j)
            std::cin >> t[i][j];
    }

    size_t n;
    std::cin >> n;

    for (size_t i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;

        std::cout << s << ':' << ' ' << solve(t, s) << '\n';
    }

    return 0;
}
