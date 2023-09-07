#include <iostream>
#include <string>
#include <vector>

void convert_12(unsigned n)
{
    constexpr int dx[4] = { +1,  0, -1,  0 };
    constexpr int dy[4] = {  0, +1,  0, -1 };
    constexpr char c[4] = { 'R', 'T', 'L', 'B' };

    std::vector<std::pair<unsigned, unsigned>> r(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> r[i].first >> r[i].second;

    unsigned pixels[10][10] = {};
    for (const std::pair<unsigned, unsigned>& p : r)
        pixels[p.first-1][p.second-1] = 1;

    std::cout << r[0].first << ' ' << r[0].second << '\n';

    std::vector<std::pair<unsigned, unsigned>> q = { r[0] };
    for (size_t i = 0; i < q.size(); ++i) {
        for (size_t j = 0; j < 4; ++j) {
            const int x = q[i].first + dx[j], y = q[i].second + dy[j];
            if (x == 0 || x == 11 || y == 0 || y == 11 || pixels[x-1][y-1] == 0)
                continue;

            if (pixels[x-1][y-1] == 1) {
                std::cout << c[j];
                q.emplace_back(x, y);
                pixels[x-1][y-1] = 0;
            }
        }
        std::cout << (i + 1 < q.size() ? ',' : '.') << '\n';

        pixels[q[i].first-1][q[i].second-1] = 0;
    }
}

void convert_21(unsigned x, unsigned y)
{
    unsigned pixels[10][10] = {};

    std::vector<std::pair<unsigned, unsigned>> q = { std::make_pair(x, y) };
    for (size_t i = 0; i < q.size(); ++i) {
        const auto [x, y] = q[i];
        pixels[x-1][y-1] = 1;

        std::string input;
        std::getline(std::cin, input);

        for (const char c : input) {
            switch (c) {
                case 'R': q.emplace_back(x + 1, y); break;
                case 'T': q.emplace_back(x, y + 1); break;
                case 'L': q.emplace_back(x - 1, y); break;
                case 'B': q.emplace_back(x, y - 1); break;
            }
        }
    }

    std::cout << q.size() << '\n';
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            if (pixels[i][j] == 1)
                std::cout << 1 + i << ' ' << 1 + j << '\n';
        }
    }
}

int main()
{
    std::string first_line;
    std::getline(std::cin, first_line);

    const size_t x = first_line.find(' ');
    if (x == std::string::npos) {
        convert_12(std::stoi(first_line));
    } else {
        convert_21(std::stoi(first_line.substr(0, x)), std::stoi(first_line.substr(x)));
    }

    return 0;
}
