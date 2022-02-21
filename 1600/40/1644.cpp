#include <iostream>
#include <string>

int main()
{
    size_t n;
    std::cin >> n;

    unsigned lb = 2, ub = 10;
    while (n-- != 0) {
        unsigned x;
        std::cin >> x;

        std::string s;
        std::cin >> s;

        if (s == "hungry")
            lb = std::max(lb, x);

        if (s == "satisfied")
            ub = std::min(ub, x);
    }

    if (lb >= ub)
        std::cout << "Inconsistent" << '\n';
    else
        std::cout << ub << '\n';

    return 0;
}
