#include <iostream>
#include <numeric>
#include <unordered_map>

using integer = unsigned long long;

unsigned raise(unsigned base, unsigned power, unsigned modulus)
{
    integer v = 1;
    for (integer b = base; power != 0; power /= 2) {
        if (power % 2 == 1) {
            v *= b;
            v %= modulus;
        }
        b *= b;
        b %= modulus;
    }
    return v;
}

unsigned solve(unsigned a, unsigned n)
{
    if (std::gcd(a, n) != 1)
        return 0;

    unsigned k = 2;
    while (k * k < n)
        ++k;

    std::unordered_map<unsigned, unsigned> x;
    for (unsigned i = k; i > 0; --i)
        x[raise(a, i * k, n)] = i;

    unsigned best = ~0u;
    for (unsigned j = 0; j < k; ++j) {
        const unsigned v = raise(a, j, n);
        if (auto it = x.find(v); it != x.end())
            best = std::min(best, it->second * k - j);
    }

    return best;
}

int main()
{
    unsigned a, n;
    std::cin >> a >> n;

    std::cout << solve(a, n) << '\n';

    return 0;
}
