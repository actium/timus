#include <iostream>
#include <vector>

int main()
{
    unsigned lb, ub;
    std::cin >> lb >> ub;

    std::vector<unsigned> s(1+ub);
    for (unsigned i = 1; i < ub; ++i) {
        for (unsigned j = 2 * i; j <= ub; j += i)
            s[j] += i;
    }

    unsigned r = ub;
    for (unsigned i = lb; i < ub; ++i) {
        if (1ull * s[i] * r < 1ull * s[r] * i)
            r = i;
    }

    std::cout << r << '\n';

    return 0;
}
