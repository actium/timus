#include <array>
#include <iostream>
#include <string>

void decode(const std::array<std::string, 4>& g, const std::array<std::string, 4>& c, std::string& p)
{
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            if (g[i][j] == 'X')
                p.push_back(c[i][j]);
        }
    }
}

void rotate(std::array<std::string, 4>& g)
{
    std::array<std::string, 4> t = {
        std::string(4, '.'),
        std::string(4, '.'),
        std::string(4, '.'),
        std::string(4, '.'),
    };

    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j)
            t[j][3-i] = g[i][j];
    }

    g = t;
}

int main()
{
    std::array<std::string, 4> g;
    for (size_t i = 0; i < 4; ++i)
        std::cin >> g[i];

    std::array<std::string, 4> c;
    for (size_t i = 0; i < 4; ++i)
        std::cin >> c[i];

    std::string p;
    for (size_t k = 0; k < 4; ++k) {
        decode(g, c, p);
        rotate(g);
    }

    std::cout << p << '\n';

    return 0;
}
