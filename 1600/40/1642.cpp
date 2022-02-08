#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    int x;
    std::cin >> x;

    std::vector<int> p(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> p[i];

    p.push_back(x);

    std::sort(p.begin(), p.end());

    const int r = *std::upper_bound(p.cbegin(), p.cend(), 0, std::less<int>());
    if (x > r) {
        std::cout << "Impossible" << '\n';
        return 0;
    }

    const int l = *std::upper_bound(p.crbegin(), p.crend(), 0, std::greater<int>());
    if (x < l) {
        std::cout << "Impossible" << '\n';
        return 0;
    }

    const int fd = x > 0 ? x : 2 * r + -x;
    const int bd = x < 0 ? -x : 2 * -l + x;

    std::cout << fd << ' ' << bd << '\n';

    return 0;
}
