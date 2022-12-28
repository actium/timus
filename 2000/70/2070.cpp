#include <iostream>
#include <vector>

int main()
{
    using integer = unsigned long long;

    constexpr size_t N = 1000000;

    integer lb, ub;
    std::cin >> lb >> ub;

    std::vector<bool> c(1 + N);
    for (integer i = 2; i <= N; ++i) {
        if (c[i])
            continue;

        for (integer j = i * i; j <= N; j += i)
            c[j] = true;
    }

    unsigned d = 0;
    for (integer i = 2; i <= N; ++i) {
        if (c[i])
            continue;

        for (integer x = i * i, p = 3; x <= ub; x *= i, ++p) {
            if (x >= lb && !c[p])
                ++d;
        }
    }

    std::cout << ub - lb + 1 - d << '\n';

    return 0;
}
