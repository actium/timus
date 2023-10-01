#include <iostream>
#include <vector>

using matrix_t = std::vector<std::vector<unsigned>>;

matrix_t multiply(const matrix_t& a, const matrix_t& b)
{
    const size_t n = a.size();

    matrix_t c(n, std::vector<unsigned>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = 0; k < n; ++k)
                c[i][j] += a[i][k] * b[k][j];

            c[i][j] = (c[i][j] != 0);
        }
    }
    return c;
}

matrix_t raise(matrix_t b, unsigned k)
{
    const size_t n = b.size();

    matrix_t v(n, std::vector<unsigned>(n));
    for (size_t i = 0; i < n; ++i)
        v[i][i] = 1;

    while (k != 0) {
        if ((k & 1) != 0)
            v = multiply(v, b);

        b = multiply(b, b);
        k /= 2;
    }
    return v;
}

const char* solve(const matrix_t& a)
{
    const size_t n = a.size();

    matrix_t b(n, std::vector<unsigned>(n));
    for (unsigned k = n * (n - 1); k <= n * (n + 1); ++k) {
        const matrix_t c = raise(a, k);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j)
                b[i][j] += c[i][j];
        }
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (b[i][j] == 0)
                return "No";
        }
    }
    return "Yes";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    matrix_t a(n, std::vector<unsigned>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cin >> a[i][j];

            a[i][j] = (a[i][j] != 0);
        }
    }

    std::cout << solve(a) << '\n';

    return 0;
}
