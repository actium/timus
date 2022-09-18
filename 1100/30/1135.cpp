#include <iostream>

int main()
{
    size_t n;
    std::cin >> n;

    unsigned k = 0, q = 0;
    for (size_t i = 0; i < n; ++i) {
        char c;
        std::cin >> c;

        if (c == '>')
            ++q;
        else
            k += q;
    }

    std::cout << k << '\n';

    return 0;
}
