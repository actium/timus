#include <iostream>
#include <vector>

void test_case(size_t n)
{
    std::vector<std::vector<unsigned>> p(n, std::vector<unsigned>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cin >> p[i][j];

            p[i][j] ^= 1;
        }
    }

    for (size_t i = 1; i < n - 1; ++i) {
        for (size_t j = 1; j < n - 1; ++j) {
            if (p[i][j] != 0)
                p[i][j] = std::min(p[i-1][j], p[i][j-1]) + 1;
        }
    }
    for (size_t i = n - 1; i-- > 1; ) {
        for (size_t j = n - 1; j-- > 1; ) {
            if (p[i][j] != 0)
                p[i][j] = std::min(p[i][j], std::min(p[i+1][j], p[i][j+1]) + 1);
        }
    }

    const auto check = [&](size_t r, size_t c) {
        const size_t rb = r - p[r][c] + 1, re = r + p[r][c];
        const size_t cb = c - p[r][c] + 1, ce = c + p[r][c];

        for (size_t i = rb; i < r; ++i) {
            for (size_t j = cb; j < c - (i - rb); ++j) {
                if (p[i][j] != 0)
                    return false;
            }
            for (size_t j = c + (i - rb) + 1; j < ce; ++j) {
                if (p[i][j] != 0)
                    return false;
            }
        }
        for (size_t i = r + 1; i < re; ++i) {
            for (size_t j = cb; j < i - r; ++ j) {
                if (p[i][j] != 0)
                    return false;
            }
            for (size_t j = ce - (i - r); j < ce; ++j) {
                if (p[i][j] != 0)
                    return false;
            }
        }
        return true;
    };

    unsigned x = 0;
    for (size_t i = 1; i < n - 1; ++i) {
        for (size_t j = 1; j < n - 1; ++j) {
            if (p[i][j] > 1 && check(i, j))
                x = std::max(x, p[i][j]);
        }
    }

    if (x != 0)
        std::cout << 2 * x - 1 << '\n';
    else
        std::cout << "No solution" << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    while (n != 0) {
        test_case(n);
        std::cin >> n;
    }

    return 0;
}
