#include <bitset>
#include <iostream>
#include <numeric>

using integer = unsigned long long;

constexpr integer b = 1000000000000ull;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::bitset<1000000> q;

    integer p = 1;

    const auto update = [&](unsigned d) {
        if (q.test(d - 1))
            p = b + 1;

        if (p <= b)
            p = std::lcm(p, d);

        for (integer i = 1; i * i <= 1000000 && p <= b; ++i) {
            if (q.test(i - 1) && d % i == 0)
                p = b + 1;
        }
    };

    for (unsigned i = 0; i < n; ++i) {
        unsigned d, t;
        std::cin >> d >> t;

        if (t == 1) {
            update(d);
        } else {
            q.set(d - 1);

            if (p % d == 0)
                p = b + 1;
        }

        if (p > b) {
            std::cout << -1 << '\n';
        } else {
            std::cout << p << '\n';
        }
    }

    return 0;
}
