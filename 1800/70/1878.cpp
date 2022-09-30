#include <algorithm>
#include <iostream>

int main()
{
    unsigned c[4] = {};
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            unsigned x;
            std::cin >> x;

            c[i/2*2 + j/2] += (x == 1);
        }
    }

    std::cout << std::min({ c[0]+c[0]+c[1]+c[2], c[0]+c[1]+c[1]+c[3], c[0]+c[2]+c[2]+c[3], c[1]+c[2]+c[3]+c[3] }) << '\n';

    return 0;
}
