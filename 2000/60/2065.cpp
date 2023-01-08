#include <iostream>

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    for (int i = k; i > 0; --i)
        std::cout << (i % 2 == 0 ? i / 2 : -i / 2) << ' ';

    for (unsigned i = k; i < n; ++i)
        std::cout << 0 << ' ';

    return 0;
}
