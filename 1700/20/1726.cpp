#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    using integer = unsigned long long;

    integer n;
    std::cin >> n;

    std::vector<integer> x(n), y(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> x[i] >> y[i];

    std::sort(x.begin(), x.end());
    std::sort(y.begin(), y.end());

    integer d = 0;
    for (size_t i = 0; i < n; ++i)
        d += (x[i] + y[i]) * (2 * i - n + 1);

    const integer k = n * (n - 1) / 2;

    std::cout << d / k << '\n';

    return 0;
}
