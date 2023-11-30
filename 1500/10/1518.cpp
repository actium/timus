#include <iostream>
#include <vector>

using integer = unsigned long long;

using matrix_t = std::vector<std::vector<integer>>;

void multiply(matrix_t& lhs, const matrix_t& rhs, unsigned modulus)
{
    const size_t n = lhs.size(), m = rhs[0].size();

    matrix_t c(n, std::vector<integer>(m));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            for (size_t k = 0; k < n; ++k)
                c[i][j] += lhs[i][k] * rhs[k][j];
        }
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            c[i][j] %= modulus;
    }

    lhs.swap(c);
}

void raise(matrix_t& base, unsigned power, unsigned modulus)
{
    matrix_t v(base.size(), std::vector<integer>(base[0].size()));
    for (size_t i = 0; i < v.size(); ++i)
        v[i][i] = 1;

    while (power != 0) {
        if (power % 2 == 1)
            multiply(v, base, modulus);

        multiply(base, base, modulus);
        power /= 2;
    }

    base.swap(v);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, x, y;
    std::cin >> n >> x >> y;

    matrix_t k(n, std::vector<integer>(1));
    for (size_t i = 0; i < n; ++i)
        std::cin >> k[i][0];

    matrix_t m(n, std::vector<integer>(n + 1));
    for (size_t i = 0; i < n; ++i)
        std::cin >> m[n-1][i];

    for (size_t i = 1; i < n; ++i)
        m[i-1][i] = 1;

    raise(m, x - n, y);
    multiply(m, k, y);

    std::cout << m[n-1][0] << '\n';

    return 0;
}
