#include <iostream>

unsigned solve(unsigned a, unsigned b)
{
    if (b % a != 0)
        return 0;

    b /= a;

    unsigned k = 1;
    for (unsigned c = 2; c * c <= b; ++c) {
        while (b % c == 0) {
            b /= c;
            ++k;
        }
    }
    return k + (b != 1);
}

void test_case()
{
    unsigned a, b;
    std::cin >> a >> b;

    std::cout << solve(a, b) << '\n';
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t t;
    std::cin >> t;

    while (t-- > 0)
        test_case();

    return 0;
}
