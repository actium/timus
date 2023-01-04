#include <iostream>
#include <vector>

void solve(std::vector<unsigned>& c)
{
    if (c[0] + c[2] + c[5] + c[7] - c[1] - c[3] - c[4] - c[6] != 0) {
        std::cout << "IMPOSSIBLE" << '\n';
        return;
    }

    unsigned s = 0;
    for (size_t i = 0; i < 8; ++i)
        s += c[i];

    const auto create = [&](size_t x, size_t y) {
        std::cout << char('A' + x) << char('A' + y) << '+' << '\n';
        ++c[x];
        ++c[y];
        s += 2;
    };

    const auto destroy = [&](size_t x, size_t y) {
        std::cout << char('A' + x) << char('A' + y) << '-' << '\n';
        --c[x];
        --c[y];
        s -= 2;
    };

    const auto destroy_some = [&] {
        constexpr size_t p[][2] = {
            {0, 1}, {1, 2}, {2, 3}, {3, 0},
            {4, 5}, {5, 6}, {6, 7}, {7, 4},
            {0, 4}, {1, 5}, {2, 6}, {3, 7},
        };
        for (const auto& q : p) {
            if (c[q[0]] != 0 && c[q[1]] != 0) {
                destroy(q[0], q[1]);
                return true;
            }
        }
        return false;
    };

    const auto create_some = [&] {
        constexpr size_t p[][4] = {
            {0, 6, 1, 5}, {1, 7, 2, 6}, {2, 4, 3, 7}, {3, 5, 0, 4},
        };
        for (const auto& q : p) {
            if (c[q[0]] != 0 && c[q[1]] != 0) {
                create(q[2], q[3]);
                break;
            }
        }
        return true;
    };

    while (s != 0) {
        destroy_some() || create_some();
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<unsigned> c(8);
    for (size_t i = 0; i < 8; ++i)
        std::cin >> c[i];

    solve(c);

    return 0;
}
