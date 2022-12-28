#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> d(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> d[i];

    unsigned x = 1;
    for (size_t i = 0; i < n && d[i] <= x; ++i)
        x += d[i];

    std::cout << x << '\n';

    return 0;
}
