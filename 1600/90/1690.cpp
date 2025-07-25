#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<size_t> p[4];
    for (size_t i = 0; i < 5 * n; ++i) {
        int x, y;
        std::cin >> x >> y;

        const size_t index = (std::abs(x) & 1) << 1 | std::abs(y) & 1;
        p[index].push_back(i);
    }

    size_t r = 0;
    while (p[r].size() < n)
        ++r;

    std::cout << "OK" << '\n';
    for (size_t i = 0; i < n; ++i)
        std::cout << p[r][i] + 1 << " \n"[i+1==n];

    return 0;
}
