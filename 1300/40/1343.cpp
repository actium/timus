#include <iostream>
#include <iomanip>

using integer = unsigned long long;

bool check(integer x)
{
    if (x % 2 == 0)
        return false;

    for (integer i = 3; i * i <= x; i += 2) {
        if (x % i == 0)
            return false;
    }

    return true;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    integer x;
    std::cin >> x;

    while (n++ < 12)
        x *= 10;

    while (!check(x))
        ++x;

    std::cout << std::setw(12) << std::setfill('0') << x << '\n';

    return 0;
}
