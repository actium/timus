#include <iostream>
#include <vector>

unsigned sum(unsigned a, unsigned b)
{
    return (a + b) % 1000000007;
}

int main()
{
    unsigned n, a, b;
    std::cin >> n >> a >> b;

    std::vector<unsigned> dp1(1+n), dp2(1+n);
    dp1[0] = dp2[0] = 1;

    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 1; j <= a && i + j <= n; ++j)
            dp1[i+j] = sum(dp1[i+j], dp2[i]);

        for (unsigned j = 1; j <= b && i + j <= n; ++j)
            dp2[i+j] = sum(dp2[i+j], dp1[i]);
    }

    std::cout << sum(dp1[n], dp2[n]) << '\n';

    return 0;
}
