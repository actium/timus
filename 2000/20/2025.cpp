#include <iostream>
#include <vector>

void solve_case()
{
    unsigned n, k;
    std::cin >> n >> k;

    std::vector<unsigned> c(k, n / k);
    for (size_t i = 0, r = n % k; i < r; ++i)
        ++c[i];

    unsigned q = 0;
    for (size_t i = 0; i < k; ++i)
        q += c[i] * (n - c[i]);

    std::cout << q / 2 << '\n';
}

int main()
{
    unsigned t;
    std::cin >> t;

    while (t-- > 0)
        solve_case();

    return 0;
}
