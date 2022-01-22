#include <iostream>
#include <vector>

void solve(std::vector<unsigned>& w)
{
    unsigned b = 0;
    for (const unsigned x : w)
        b += x;

    unsigned d = ~0u;
    for (unsigned i = 0, k = 1 << w.size(); i < k; ++i) {
        unsigned s = 0;
        for (unsigned x = i; x != 0; x -= x & -x)
            s += w[__builtin_ctz(x)];

        d = std::min<unsigned>(d, std::abs(int(b - 2 * s)));
    }

    std::cout << d << '\n';
}

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> w(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> w[i];

    solve(w);

    return 0;
}
