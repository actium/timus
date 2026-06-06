#include <iostream>

using integer = unsigned long long;

integer square_root(integer x)
{
    integer lb = 1, ub = x;
    while (ub - lb > 1) {
        const auto mid = (lb + ub) / 2;
        (mid <= x / mid ? lb : ub) = mid;
    }
    return lb;
}

integer solve(integer n)
{
    const auto count = [n](integer lb, integer ub) {
        return n / lb - n / ub;
    };

    integer lb = square_root(n) + 1, d = 1;
    while (count(lb, lb + d) == d) {
        lb += d;
        d *= 2;
    }
    for (integer ub = lb + d; ub - lb > 1; ) {
        const auto mid = (lb + ub) / 2;
        (count(lb, mid) == mid - lb ? lb : ub) = mid;
    }
    return lb;
}

void test_case()
{
    integer n;
    std::cin >> n;

    std::cout << solve(n) << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t t;
    std::cin >> t;

    while (t-- > 0)
        test_case();

    return 0;
}
