#include <iostream>

unsigned solve(int x, int y, int n)
{
    if (x <= y)
        return 0;

    const int b = std::min(10 * n, ((10 * x + 5) * n - 1) / 100);
    return (n * (10 * y + 5) - 100 * b) / (100 - (10 * y + 5)) + 1;
}

int main()
{
    double x, y;
    std::cin >> x >> y;

    unsigned n;
    std::cin >> n;

    std::cout << solve(x * 10 + 0.5, y * 10 + 0.5, n) << '\n';

    return 0;
}
