#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    unsigned s = 0;
    for (unsigned i = 0; i < n; ++i) {
        unsigned x;
        std::cin >> x;

        s += x;
    }

    std::cout << std::fixed << double(s) / n << '\n';

    return 0;
}
