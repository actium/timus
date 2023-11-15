#include <algorithm>
#include <iostream>
#include <vector>

std::vector<unsigned> prepare(unsigned base, unsigned radix)
{
    std::vector<unsigned> t(radix);
    {
        unsigned x[20] = {};
        for (unsigned i = 1; i < radix; ++i) {
            t[i] = t[i-1] + 1;

            for (unsigned j = 0; ++x[j] >= base; ++j) {
                x[j] -= base;
                t[i] -= base - 1;
            }
        }
    }
    return t;
}

unsigned sum_digits(unsigned x, unsigned base, unsigned radix)
{
    if (base == 2)
        return __builtin_popcount(x);

    if (base == 4)
        return __builtin_popcount(x & 0xAAAAAAAA) * 2
             + __builtin_popcount(x & 0x55555555);

    if (base == 8) {
        return __builtin_popcount(x & 0x24924924) * 4
             + __builtin_popcount(x & 0x12492492) * 2
             + __builtin_popcount(x & 0x09249249);
    }

    static const auto t = prepare(base, radix);
    return t[x];
}

unsigned add(std::vector<unsigned>& lhs, const std::vector<unsigned>& rhs, unsigned base, unsigned radix)
{
    const size_t n = rhs.size();
    lhs.resize(n + 1);

    unsigned s = 0;
    for (size_t i = 0; i < n; ++i) {
        unsigned long long digit = lhs[i];
        digit += rhs[i];
        lhs[i] = digit;
        lhs[i+1] += digit >> 32;

        if (base != 2 && base != 4) {
            if (lhs[i] >= radix) {
                lhs[i] -= radix;
                ++lhs[i+1];
            }
        }

        s += sum_digits(lhs[i], base, radix);
    }
    s += sum_digits(lhs[n], base, radix);

    if (lhs.back() == 0)
        lhs.pop_back();

    return s;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned k, n;
    std::cin >> k >> n;

    unsigned m = k;
    while (m * k <= 1000000)
        m *= k;

    std::vector<std::pair<unsigned, unsigned>> s(n);
    s[0] = std::make_pair(1, 1);
    s[1] = std::make_pair(1, 2);

    std::vector<unsigned> x[2];
    for (size_t i = 0; i < 2; ++i) {
        x[i].reserve(2000);
        x[i].push_back(1);
    }

    for (unsigned i = 2; i < n; ++i) {
        const unsigned d = add(x[i % 2], x[i % 2 ^ 1], k, m);
        s[i] = std::make_pair(d, i + 1);
    }

    std::sort(s.begin(), s.end());

    for (const auto& x : s)
        std::cout << x.second << ' ';

    return 0;
}
