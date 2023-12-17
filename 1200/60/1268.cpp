#include <iostream>
#include <vector>

constexpr unsigned primes[] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 71, 73, 79,
    83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
    173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251,
};

std::vector<unsigned> factors(unsigned n)
{
    std::vector<unsigned> s;
    for (const unsigned p : primes) {
        if (p >= n)
            break;

        if (n % p == 0) {
            s.push_back(p);
            while (n % p == 0)
                n /= p;
        }
    }
    if (n != 1)
        s.push_back(n);

    return s;
}

unsigned raise(unsigned b, unsigned p, unsigned m)
{
    unsigned v = 1;
    while (p != 0) {
        if (p % 2 == 1)
            v = v * b % m;

        b = b * b % m;
        p /= 2;
    }
    return v;
}

unsigned solve(unsigned n)
{
    const auto check = [&](unsigned g) {
        for (const unsigned f : factors(n-1)) {
            if (raise(g, (n-1) / f, n) == 1)
                return false;
        }
        return true;
    };

    unsigned p = n - 1;
    while (p > 1 && !check(p))
        --p;

    return p;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned t;
    std::cin >> t;

    for (unsigned i = 0; i < t; ++i) {
        unsigned n;
        std::cin >> n;

        std::cout << solve(n) << '\n';
    }

    return 0;
}
