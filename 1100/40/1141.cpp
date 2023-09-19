#include <iostream>
#include <utility>
#include <vector>

std::vector<unsigned> primes;

void prepare()
{
    const auto is_prime = [](unsigned n) {
        for (unsigned i = 3; i * i <= n; i += 2) {
            if (n % i == 0)
                return false;
        }
        return true;
    };

    for (unsigned i = 3; i * i <= 32000; i += 2) {
        if (is_prime(i))
            primes.push_back(i);
    }
}

unsigned raise(unsigned base, unsigned power, unsigned modulus)
{
    unsigned v = 1;
    while (power != 0) {
        if (power & 1)
            v = v * base % modulus;

        base = base * base % modulus;
        power >>= 1;
    }
    return v;
}

unsigned euclidean(int a, unsigned n)
{
    int x = 1, y = 0;
    for (int b = n; b != 0; ) {
        const int t = a / b;
        a = std::exchange(b, a - t * b);
        x = std::exchange(y, x - t * y);
    }

    return x < 0 ? x + n : x;
}

void test_case(unsigned)
{
    unsigned e, n, c;
    std::cin >> e >> n >> c;

    unsigned p, q;
    for (const unsigned x : primes) {
        if (n % x == 0) {
            p = x;
            q = n / x;
            break;
        }
    }

    const unsigned d = euclidean(e, (p - 1) * (q - 1));
    std::cout << raise(c, d, n) << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    prepare();

    unsigned k;
    std::cin >> k;

    for (unsigned i = 0; i < k; ++i)
        test_case(i);

    return 0;
}
