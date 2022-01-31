#include <iostream>

int main()
{
    size_t n;
    std::cin >> n;

    unsigned s = 0, x = 0;
    for (size_t i = 0; i < n; ++i) {
        unsigned a;
        std::cin >> a;

        s += a;
        x = std::max(x, a);
    }

    std::cout << s + x << '\n';

    return 0;
}
