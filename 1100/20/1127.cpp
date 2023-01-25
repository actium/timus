#include <algorithm>
#include <iostream>
#include <vector>

constexpr size_t t[24][4] = {
    {0, 1, 3, 2}, {0, 2, 3, 1}, {0, 4, 3, 5}, {0, 5, 3, 4},
    {1, 0, 2, 3}, {1, 3, 2, 0}, {1, 4, 2, 5}, {1, 5, 2, 4},
    {2, 0, 1, 3}, {2, 3, 1, 0}, {2, 4, 1, 5}, {2, 5, 1, 4},
    {3, 1, 0, 2}, {3, 2, 0, 1}, {3, 4, 0, 5}, {3, 5, 0, 4},
    {4, 0, 5, 3}, {4, 1, 5, 2}, {4, 2, 5, 1}, {4, 3, 5, 0},
    {5, 0, 4, 3}, {5, 1, 4, 2}, {5, 2, 4, 1}, {5, 3, 4, 0},
};

unsigned encode(char a, char b, char c, char d)
{
    return unsigned(a) << 24 | unsigned(b) << 16 | unsigned(c) << 8 | unsigned(d);
}

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> s;
    s.reserve(24 * n);
    for (size_t i = 0; i < n; ++i) {
        std::string c;
        std::cin >> c;

        for (const auto p : t)
            s.push_back(encode(c[p[0]], c[p[1]], c[p[2]], c[p[3]]));
    }

    std::sort(s.begin(), s.end());

    size_t k = 0;
    {
        s.push_back(0);
        for (size_t i = 1, j = 0; i < s.size(); ++i) {
            if (s[i] != s[j]) {
                k = std::max(k, i - j);
                j = i;
            }
        }
    }

    std::cout << k << '\n';

    return 0;
}
