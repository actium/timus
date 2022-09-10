#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    using integer = unsigned long long;

    std::vector<integer> x(3);
    for (size_t i = 0; i < 3; ++i)
        std::cin >> x[i];

    for (integer d = ~integer(0); d != 0; x.push_back(d)) {
        std::sort(x.begin(), x.end());
        for (size_t i = 1; i < x.size(); ++i)
            d = std::min(d, x[i] - x[i-1]);
    }

    std::cout << x.size() - 3 << '\n';

    return 0;
}
