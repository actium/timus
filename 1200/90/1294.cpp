#include <iostream>

#include <cmath>

int main()
{
    int d, p, q, b;
    std::cin >> d >> p >> q >> b;

    if (p * d == q * b) {
        std::cout << "Impossible." << '\n';
    } else {
        const auto cc = double(p * b - q * d) * (p * q - b * d) / (q * b - p * d);

        const unsigned x = std::round(std::sqrt(cc) * 1000);
        std::cout << "Distance is " << x << " km." << '\n';
    }

    return 0;
}
