#include <iostream>
#include <string>

int main()
{
    unsigned b, r, y;
    std::cin >> b >> r >> y;

    unsigned k;
    std::cin >> k;

    unsigned q = 1;
    for (unsigned i = 0; i < k; ++i) {
        std::string p;
        std::cin >> p;

        if (p == "Blue")
            q *= b;
        if (p == "Red")
            q *= r;
        if (p == "Yellow")
            q *= y;
    }

    std::cout << q << '\n';

    return 0;
}
