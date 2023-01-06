#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<long long> v(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> v[i];

    size_t b = 1;
    for (size_t i = 2; i < n; ++i) {
        if (std::abs(v[b] - v[b-1]) < std::abs(v[i] - v[i-1]))
            b = i;
    }

    std::cout << b << ' ' << b + 1 << '\n';

    return 0;
}
