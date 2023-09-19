#include <iostream>

unsigned f(unsigned k)
{
    constexpr unsigned t[10] = { 0, 1, 8, 27, 64, 125, 216, 343, 512, 729 };

    unsigned s = 0;
    while (k != 0) {
        s += t[k % 10];
        k /= 10;
    }
    return s;
}

void test_case(unsigned)
{
    unsigned n, k, l;
    std::cin >> n >> k >> l;

    for (unsigned i = 1, q = 0; i < n && k != q; ++i) {
        q = k;
        k = f(k);
    }

    std::cout << k - l << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned t;
    std::cin >> t;

    for (unsigned i = 0; i < t; ++i)
        test_case(i);

    return 0;
}
