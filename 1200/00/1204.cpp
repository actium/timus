#include <iostream>
#include <vector>

std::vector<unsigned> primes;

void initialize()
{
    constexpr size_t N = 32000;

    bool c[N] = {};
    for (unsigned i = 2; i < N; ++i) {
        if (c[i])
            continue;

        for (unsigned j = i * i; j < N; j += i)
            c[j] = true;

        primes.push_back(i);
    }
}

std::pair<long long, long long> euclidean(unsigned p, unsigned q)
{
    if (p == 0)
        return std::make_pair(0, 1);

    const auto r = euclidean(q % p, p);
    return std::make_pair(r.second - q / p * r.first, r.first);
}

void test_case()
{
    unsigned n;
    std::cin >> n;

    const auto factor = [](unsigned n) {
        for (const unsigned x : primes) {
            if (n % x == 0)
                return x;
        }
        return n;
    };

    const unsigned p = factor(n), q = n / p;

    const auto r = euclidean(p, q);

    auto x1 = (r.first > 0 ? p * r.first : q * r.second) % n, x2 = n - x1 + 1;
    if (x2 < x1)
        std::swap(x1, x2);

    const auto print = [n](unsigned x) {
        if (x < n)
            std::cout << x << ' ';
    };

    print(0);
    print(1);
    print(x1);
    print(x2);

    std::cout << '\n';
}

int main()
{
    initialize();

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t;
    std::cin >> t;

    while (t-- > 0)
        test_case();

    return 0;
}
