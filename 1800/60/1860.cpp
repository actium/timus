#include <iostream>
#include <vector>

constexpr unsigned N = 1000000, M = 1000000007;

unsigned solve(unsigned n)
{
    std::vector<unsigned> fib(1 + n, 1);
    for (unsigned i = 2; i <= n; ++i)
        fib[i] = (fib[i-1] + fib[i-2]) % M;

    std::vector<unsigned> p;

    std::vector<bool> c(1 + n);
    for (unsigned i = 2; i <= n; ++i) {
        if (c[i])
            continue;

        p.emplace_back();

        for (unsigned j = i; j <= n; j += i) {
            for (unsigned m = j; m % i == 0; m /= i) {
                p.back() += fib[n - j];
                p.back() %= M;
            }

            c[j] = true;
        }
    }

    unsigned long long k = 1;
    for (const unsigned q : p) {
        k *= 1 + q;
        k %= M;
    }
    return k;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::cout << solve(n) << '\n';

    return 0;
}
