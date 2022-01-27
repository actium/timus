#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    unsigned f[3] = {};
    for (unsigned i = 0; i < n; ++i) {
        unsigned v;
        std::cin >> v;

        ++f[v-3];
    }

    if (f[0] != 0) {
        std::cout << "None" << '\n';
    } else if (f[2] == n) {
        std::cout << "Named" << '\n';
    } else if (6 * f[0] + 8 * f[1] + 10 * f[2] >= 9 * n) {
        std::cout << "High" << '\n';
    } else {
        std::cout << "Common" << '\n';
    }

    return 0;
}
