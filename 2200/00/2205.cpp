#include <iostream>
#include <vector>

constexpr unsigned K = 10000000;

unsigned spf[1+K];

void initialize()
{
    std::vector<unsigned> primes;
    for (unsigned i = 2; i <= K; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }

        for (const unsigned p : primes) {
            if (p > spf[i] || i * p > K)
                break;

            spf[i * p] = p;
        }
    }
}

unsigned solve(unsigned a, unsigned b)
{
    while (a != b) {
        if (a > b)
            a /= spf[a];
        else
            b /= spf[b];
    }
    return a;
}

void test_case()
{
    unsigned a, b;
    std::cin >> a >> b;

    std::cout << solve(a, b) << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    initialize();

    size_t t;
    std::cin >> t;

    while (t-- > 0)
        test_case();

    return 0;
}
