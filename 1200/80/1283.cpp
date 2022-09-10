#include <iostream>

int main()
{
    double a, b, c;
    std::cin >> a >> b >> c;

    unsigned t = 0;
    while (a > b) {
        a -= a * c / 100;
        ++t;
    }

    std::cout << t << '\n';

    return 0;
}
