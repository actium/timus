#include <iostream>

int main()
{
    using integer = unsigned long long;
    
    integer n;
    std::cin >> n;

    unsigned k = 0;
    for (integer i = 2; i < 2500000 && i * i <= n; ++i) {
        while (n % i == 0) {
            ++k;
            n /= i;
        }
    }
    k += (n != 1);

    std::cout << (k == 20 ? "Yes" : "No") << '\n';

    return 0;
}
