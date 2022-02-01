#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    unsigned f[1 + 25000] = {};
    while (n-- > 0) {
        unsigned p;
        std::cin >> p;

        ++f[p];
    }

    for (size_t i = 25000; i > 0; --i) {
        while (f[i]-- > 0)
            std::cout << i << '\n';
    }

    return 0;
}
