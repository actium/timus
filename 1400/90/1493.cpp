#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    const auto sum = [](unsigned x) {
        unsigned s = 0;
        for (unsigned i = 0; i < 3; ++i) {
            s += x % 10;
            x /= 10;
        }
        return s;
    };

    const auto test = [&](unsigned x) {
        const unsigned s1 = sum(x), s2 = sum(x / 1000);
        return s1 == s2;
    };

    if (test(n - 1) || test(n + 1))
        std::cout << "Yes" << '\n';
    else
        std::cout << "No" << '\n';

    return 0;
}
