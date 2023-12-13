#include <iostream>
#include <string>

using integer = unsigned long long;

constexpr integer powers[18] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
    100000000, 1000000000, 10000000000, 100000000000,
    1000000000000, 10000000000000, 100000000000000,
    1000000000000000, 10000000000000000, 100000000000000000,
};

integer count(std::string_view n)
{
    if (n.empty())
        return 0;

    const unsigned d = n[0] - '0';

    n.remove_prefix(1);
    if (n.empty())
        return d != 0 ? 1 : 0;

    integer p = 0;
    if (d == 1)
        p = std::strtoull(n.data(), nullptr, 10) + 1;
    if (d > 1)
        p = powers[n.length()];

    const integer q = d * n.length() * powers[n.length()-1];
    return p + q + count(n);
}

void solve(integer n)
{
    const auto count = [](integer x) {
        const std::string v = std::to_string(x);
        return ::count(v);
    };

    integer lb = 0, ub = 999999999999999999;
    while (lb + 1 < ub) {
        const integer mid = (lb + ub) / 2;
        (count(mid) >= n ? ub : lb) = mid;
    }

    if (count(ub) == n) {
        std::cout << ub << '\n';
    } else {
        std::cout << "Petr lies" << '\n';
    }
}

int main()
{
    integer n;
    std::cin >> n;

    solve(n);

    return 0;
}
