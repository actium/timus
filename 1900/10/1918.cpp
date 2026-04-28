#include <iostream>
#include <vector>

constexpr unsigned M = 1'000'000'007;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<unsigned> t(1+n);
    t[1] = 1;
    for (unsigned i = 2; i <= n; ++i) {
        unsigned sum = 0, power = i;
        for (unsigned j = i-1; j != 0; --j) {
            sum = (sum + 1ull * t[j] * power) % M;
            power = 1ull * power * i % M;
        }
        t[i] = (M + power - sum) % M;
    }

    std::cout << t[n] << '\n';

    return 0;
}
