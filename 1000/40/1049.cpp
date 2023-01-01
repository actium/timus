#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<unsigned> f;
    for (unsigned i = 0; i < 10; ++i) {
        unsigned a;
        std::cin >> a;

        for (unsigned x = 2; x * x <= a; ++x) {
            while (a % x == 0) {
                f.push_back(x);
                a /= x;
            }
        }
        if (a != 1)
            f.push_back(a);
    }

    std::sort(f.begin(), f.end());

    unsigned p = 1, q = 1;
    f.push_back(0);
    for (size_t i = 1; i < f.size(); ++i) {
        if (f[i] == f[i-1]) {
            ++q;
        } else {
            p *= q + 1;
            q = 1;
        }
    }

    std::cout << p % 10 << '\n';

    return 0;
}
