#include <iostream>

unsigned count(unsigned n)
{
    unsigned dp[82] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    for (unsigned i = 9; i > 1; --i) {
        for (unsigned j = 81; j > 0; --j) {
            for (unsigned k = 1; k < 10 && k <= j; ++k) {
                dp[j] += dp[j-k];
            }
        }
    }
    dp[1] += 1;

    return dp[n];
}

int main()
{
    unsigned n;
    std::cin >> n;

    std::cout << count(n) << '\n';

    return 0;
}
