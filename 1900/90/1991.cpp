#include <iostream>

int main()
{
    size_t n, k;
    std::cin >> n >> k;

    unsigned q1 = 0, q2 = 0;
    for (size_t i = 0; i < n; ++i) {
        unsigned a;
        std::cin >> a;

        if (a > k)
            q1 += a - k;
        else
            q2 += k - a;
    }

    std::cout << q1 << ' ' << q2 << '\n';

    return 0;
}
