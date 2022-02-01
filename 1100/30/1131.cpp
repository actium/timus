#include <iostream>

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    unsigned t = 0, x = 1;
    while (x < k && x < n) {
        ++t;
        x *= 2;
    }

    if (x < n)
        t += (n - x + k - 1) / k;

    std::cout << t << '\n';

    return 0;
}
