#include <complex>
#include <iostream>
#include <string>
#include <vector>

#include <cmath>
#include <cstdint>

namespace fft {

    using Number = std::complex<double>;

    const double PI = acos(-1);

    unsigned base = 1;

    std::vector<Number> rts = { Number(0, 0), Number(1, 0) };
    std::vector<unsigned> rev = { 0, 1 };

    void ensure_base(size_t x)
    {
        if (x <= base)
            return;

        const size_t q = 1 << x;

        rev.resize(q);
        for (size_t i = 0; i < q; ++i)
            rev[i] = rev[i/2] / 2 + static_cast<unsigned>((i & 1) << (x - 1));

        rts.resize(q);
        while (base < x) {
            const double angle = 2 * PI / (1 << (base + 1));

            for (size_t i = 1 << (base - 1); i < (1u << base); ++i) {
                rts[i << 1] = rts[i];

                const double ax = angle * static_cast<double>(2 * i + 1 - (1 << base));
                rts[(i << 1) + 1] = Number(cos(ax), sin(ax));
            }

            ++base;
        }
    }

    void compute(std::vector<Number>& data)
    {
        const size_t sz = data.size(), z = __builtin_ctzll(sz);

        ensure_base(z);

        const size_t dx = base - z;

        for (size_t i = 0; i < sz; ++i) {
            if (i < (rev[i] >> dx))
                std::swap(data[i], data[rev[i] >> dx]);
        }

        for (size_t k = 1; k < sz; k <<= 1) {
            for (size_t i = 0; i < sz; i += 2 * k) {
                for (size_t j = 0; j < k; ++j) {
                    const Number z = data[i + j + k] * rts[j + k];
                    data[i + j + k] = data[i + j] - z;
                    data[i + j] += z;
                }
            }
        }
    }

    void multiply(const std::vector<uint8_t>& sa, const std::vector<uint8_t>& sb, std::vector<unsigned>& v)
    {
        const size_t q = sa.size() + sb.size() - 1;

        size_t x = 0;
        while ((1u << x) < q)
            ++x;

        ensure_base(x);

        const size_t sz = 1 << x;

        std::vector<Number> fa(sz);
        for (size_t i = 0; i < sa.size(); ++i)
            fa[i] = sa[i];
        for (size_t i = 0; i < sb.size(); ++i)
            fa[i].imag(sb[i]);

        compute(fa);

        const Number r(0, -0.25 / static_cast<double>(sz));
        for (size_t i = 0; i <= sz / 2; ++i) {
            const size_t j = (sz - i) & (sz - 1);

            const Number x = fa[i] * fa[i], y = fa[j] * fa[j], z = (y - std::conj(x)) * r;
            if (i != j)
                fa[j] = (x - std::conj(y)) * r;

            fa[i] = z;
        }

        compute(fa);

        v.resize(q);
        for (size_t i = 0; i < q; ++i)
            v[i] += static_cast<unsigned>(round(fa[i].real()));
    }

} // namespace fft

void solve(const std::vector<uint8_t> (& p)[8][2], const std::vector<uint8_t> (& q)[8][2])
{
    const size_t n = p[0][0].size(), m = q[0][0].size();

    std::vector<unsigned> v[8];
    for (size_t k = 0; k < 8; ++k) {
        fft::multiply(p[k][1], q[k][1], v[k]);

        std::vector<unsigned> ps(1+n);
        for (size_t i = 0; i < n; ++i)
            ps[i+1] = ps[i] + p[k][1][i];

        unsigned c = 0;
        for (size_t i = 0; i < m; ++i)
            c += q[k][1][i];

        for (size_t i = m-1; i < n; ++i)
            v[k][i] = ps[i+1] - ps[i+1-m] + c - 2 * v[k][i];
    }

    for (size_t i = 1; i < 7; ++i) {
        for (size_t j = 0; j < v[i].size(); ++j)
            v[0][j] += v[i][j];
    }

    std::pair<unsigned, size_t> b = { ~0u, 0 };
    for (size_t i = m - 1; i < n; ++i) {
        if (v[0][i] == 0 && v[7][i] < b.first) {
            b.first = v[7][i];
            b.second = i - (m - 1);
        }
    }

    if (b.first != ~0u) {
        std::cout << "Yes" << '\n';
        std::cout << b.first << ' ' << b.second + 1 << '\n';
    } else {
        std::cout << "No" << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<uint8_t> p[8][2];
    for (size_t i = 0; i < 8; ++i) {
        for (size_t j = 0; j < 2; ++j)
            p[i][j].resize(n);
    }

    for (size_t i = 0; i < n; ++i) {
        std::string x;
        std::cin >> x;

        for (size_t j = 0; j < 8; ++j)
            p[j][x[j]-'0'][i] = 1;
    }

    std::vector<uint8_t> q[8][2];
    for (size_t i = 0; i < 8; ++i) {
        for (size_t j = 0; j < 2; ++j)
            q[i][j].resize(m);
    }

    for (size_t i = 0; i < m; ++i) {
        std::string x;
        std::cin >> x;

        for (size_t j = 0; j < 8; ++j)
            q[j][x[j]-'0'][m-i-1] = 1;
    }

    solve(p, q);

    return 0;
}
