#include <iostream>
#include <vector>

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    m %= n;

    for (size_t i = 0; i < 10; ++i)
        std::cout << a[(m + i) % n];

    std::cout << '\n';

    return 0;
}
