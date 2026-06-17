#include <iostream>
#include <string>
#include <vector>

using integer = unsigned long long;

constexpr unsigned masks[15] = {
    0x0000, 0x000F, 0x00F0, 0x00FF, 0x0F00,
    0x0F0F, 0x0FF0, 0x0FFF, 0xF000, 0xF00F,
    0xF0F0, 0xF0FF, 0xFF00, 0xFF0F, 0xFFF0,
};

void solve(const std::vector<unsigned>& s)
{
    integer sums[4] = {};

    std::vector<unsigned> c(1 << 20);
    for (const auto id : s) {
        for (const auto mask : masks) {
            const auto x = (mask & 0x0001) << 16| (mask & 0x0010) << 13 | (mask & 0x0100) << 10 | (mask & 0x1000) << 7;
            sums[__builtin_popcount(mask)>>2] += c[x | (id & mask)]++;
        }
    }

    sums[2] -= 3 * sums[3];
    sums[1] -= 2 * sums[2] + 3 * sums[3];
    sums[0] -= sums[1] + sums[2] + sums[3];

    std::cout << sums[3] << ' ' << sums[2] << ' ' << sums[1] << ' ' << sums[0] << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> ids(n);
    for (size_t i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;

        ids[i] = std::stoi(s, nullptr, 16);
    }

    solve(ids);

    return 0;
}
