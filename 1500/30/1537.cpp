#include <iostream>
#include <vector>

int main()
{
    unsigned k, p;
    std::cin >> k >> p;

    std::vector<unsigned> q(1 + k);
    if (p != 1) {
        q[2] = 1;
        for (unsigned i = 3; i <= k; ++i) {
            q[i] = q[i-1];

            if (i % 2 == 0) {
                q[i] += q[i / 2];
                q[i] %= p;
            }
        }
    }
    std::cout << q[k] << '\n';

    return 0;
}
