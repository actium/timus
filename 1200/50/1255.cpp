#include <iostream>

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    if (n < k) {
        std::cout << 0 << '\n';
    } else {
        const auto r = n % k, m = std::min(r, k - r);
        std::cout << (n * n - m * m) / k << '\n';
    }

    return 0;
}
