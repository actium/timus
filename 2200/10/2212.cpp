#include <iostream>
#include <vector>

constexpr unsigned M = 998244353, R = 3;

unsigned raise(unsigned b, unsigned p)
{
    unsigned v = 1;
    while (p != 0) {
        if (p % 2 == 1)
            v = 1ull * v * b % M;

        b = 1ull * b * b % M;
        p /= 2;
    }
    return v;
}

void NTT(std::vector<unsigned>& a, bool invert)
{
    const size_t n = a.size();

    for (size_t i = 1, j = 0; i < n; ++i) {
        unsigned bit = n >> 1;
        while ((j & bit) != 0) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;

        if (i < j)
            std::swap(a[i], a[j]);
    }

    for (size_t k = 2; k <= n; k <<= 1) {
        auto q = raise(R, (M - 1) / k);
        if (invert)
            q = raise(q, M - 2);

        for (size_t i = 0; i < n; i += k) {
            unsigned w = 1, h = k >> 1;
            for (size_t j = 0; j < h; ++j) {
                const unsigned u = a[i+j], v = 1ull * a[i+j+h] * w % M;
                a[i+j] = (u + v) % M;
                a[i+j+h] = (M + u - v) % M;
                w = 1ull * w * q % M;
            }
        }
    }

    if (invert) {
        const auto x = raise(n, M - 2);
        for (size_t i = 0; i < n; ++i)
            a[i] = 1ull * a[i] * x % M;
    }
}

void convolution(std::vector<unsigned>& a, std::vector<unsigned>& b)
{
    const size_t m = a.size() + b.size() - 1;

    size_t n = 1;
    while (n < m)
        n *= 2;

    a.resize(n);
    NTT(a, false);

    b.resize(n);
    NTT(b, false);

    for (size_t i = 0; i < n; ++i)
        a[i] = 1ull * a[i] * b[i] % M;

    NTT(a, true);
}

void solve(std::vector<unsigned>& a, unsigned q)
{
    const size_t n = a.size();

    std::vector<unsigned> t(n+1, 1);
    for (size_t i = 2; i <= n; ++i)
        t[i] = M - 1ull * (M / i) * t[M % i] % M;

    std::vector<unsigned> b(n, 1);
    for (size_t i = 1; i < n; ++i)
        b[i] = 1ull * b[i-1] * (q + i - 1) % M * t[i] % M;

    convolution(a, b);

    for (size_t i = 0; i < n; ++i)
        std::cout << a[i] << " \n"[i+1==n];
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    unsigned q;
    std::cin >> q;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    solve(a, q);

    return 0;
}
