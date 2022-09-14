#include <iostream>

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    const unsigned d = std::min(k - 1, n - k);

    std::cout << std::max<int>(n - d - 3, 0) << '\n';

    return 0;
}
