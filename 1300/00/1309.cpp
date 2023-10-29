#include <iostream>

constexpr unsigned M = 9973;

unsigned p[] = {
       0, 5392, 1890,   84, 6520, 3149, 2416, 2835,   80, 8614,  742, 7696, 6823, 9492, 7710, 9444,
     510,  118, 6522, 3213, 4499, 6178, 4565,  763, 1071, 8875, 2688, 9145, 1211, 9480, 4056, 1817,
    8661, 5467, 3358, 2892, 2205, 8691, 1963, 2386, 8401, 1047, 3691, 6824,  825, 7728, 6797, 1720,
    8194, 9901, 2823, 1952, 9344, 5022, 1421, 6116, 4511, 1289, 2133, 7494, 7298, 5012, 9638, 8753,
    5968, 4029, 4804, 9556,  924, 1497, 5886, 6078, 2085, 3876,  268, 2910, 8962, 2970, 1015, 3931,
    1103, 4872, 4054,  346, 1119,  931, 4454, 6530, 1722, 4266, 9888, 7961, 2891,  885, 4461, 7731,
    3316, 2155,   93, 2871, 9710
};

int main()
{
    using integer = long long;

    unsigned n;
    std::cin >> n;

    const unsigned b = n / 1000000, r = n % 1000000;

    integer f = p[b], x = n - r + 1;
    for (unsigned i = 1; i <= r; ++i, ++x) {
        const integer u = x * x % M * x % M, v = u * x % M * x % M;
        f = f * (v - x + 7) - (v - u - 3 * x);
        f = (f % M + M) % M;
    }

    std::cout << f << '\n';

    return 0;
}