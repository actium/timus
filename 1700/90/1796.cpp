#include <iostream>
#include <vector>

int main()
{
    constexpr unsigned v[6] = { 10, 50, 100, 500, 1000, 5000 };

    unsigned k[6];
    for (size_t i = 0; i < 6; ++i)
        std::cin >> k[i];

    unsigned p;
    std::cin >> p;

    unsigned s = 0;
    for (size_t i = 0; i < 6; ++i)
        s += k[i] * v[i];

    size_t i = 0;
    while (k[i] == 0)
        ++i;

    std::vector<unsigned> c;
    for (unsigned x = (s - v[i]) / p + 1; x <= s / p; ++x)
        c.push_back(x);

    std::cout << c.size() << '\n';
    for (const unsigned x : c)
        std::cout << x << ' ';

    return 0;
}
