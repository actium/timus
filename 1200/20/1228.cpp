#include <iostream>

int main()
{
    unsigned n, s;
    std::cin >> n >> s;

    for (unsigned i = 0; i < n; ++i) {
        unsigned d;
        std::cin >> d;

        std::cout << s / d - 1 << ' ';
        s = d;
    }

    return 0;
}
