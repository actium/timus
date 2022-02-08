#include <iostream>
#include <string>

int main()
{
    std::string a;
    std::cin >> a;

    const auto test = [&a](unsigned k) {
        const unsigned m = k - 1;

        unsigned b = 1, v = 0;
        for (const char c : a) {
            const unsigned d = isdigit(c) ? c - '0' : c - 'A' + 10;
            if (d >= k)
                return false;

            v = (v + d * b) % m;
            b = b * k % m;
        }
        return v == 0;
    };

    unsigned k = 2;
    while (k <= 36 && !test(k))
        ++k;

    if (k > 36)
        std::cout << "No solution." << '\n';
    else
        std::cout << k << '\n';

    return 0;
}
