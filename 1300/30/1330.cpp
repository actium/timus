#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<int> k(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> k[i];

    std::vector<int> ps(1 + n);
    for (size_t i = 0; i < n; ++i)
        ps[i+1] = ps[i] + k[i];

    unsigned q;
    std::cin >> q;

    while (q-- != 0) {
        unsigned i, j;
        std::cin >> i >> j;

        std::cout << ps[j] - ps[i-1] << '\n';
    }

    return 0;
}
