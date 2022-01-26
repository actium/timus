#include <iostream>

unsigned search(unsigned k)
{
    unsigned lb = 0, ub = 92682;
    while (lb + 1 < ub) {
        const unsigned mid = (lb + ub) / 2;

        const auto x = mid * (mid + 1ull) / 2 + 1;
        if (x == k)
            return 1;

        (x < k ? lb : ub) = mid;
    }
    return k == 1;
}

int main()
{
    unsigned n;
    std::cin >> n;

    while (n-- != 0) {
        unsigned k;
        std::cin >> k;

        std::cout << search(k) << ' ';
    }

    return 0;
}
