#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, k, p;
    std::cin >> n >> k >> p;

    std::vector<std::vector<unsigned>> C(1+n+k, std::vector<unsigned>(1+n+k));
    for (unsigned i = 0; i <= n+k; ++i) {
        C[i][0] = 1;
        C[i][i] = 1;
        for (unsigned j = 1; j < i; ++j)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % p;
    }

    unsigned q = C[n+k-1][k-1];
    if (k != 1) {
        for (unsigned b = 1; 2 * b <= n; ++b) {
            const unsigned s = (p + C[n][b] - C[n][b-1]) % p;
            const unsigned t1 = 1ull * C[n-b+k-1][k-1] * C[b+k-2][k-2] % p;
            const unsigned t2 = 1ull * C[n-b+k-1][k-2] * C[b+k-2][k-1] % p;
            const unsigned t = (p + t1 - t2) % p;
            q = (q + 1ull * s * t) % p;
        }
    }

    std::cout << 1 + q << '\n';

    return 0;
}
