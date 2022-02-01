#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    if (n < 5) {
        constexpr const char* s[4] = { "88", "68", "06", "16" };

        while (n-- > 0)
            std::cout << s[n] << ' ';
    } else {
        std::cout << "Glupenky Pierre" << '\n';
    }

    return 0;
}
