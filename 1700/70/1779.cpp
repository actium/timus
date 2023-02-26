#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::vector<std::pair<unsigned, unsigned>> e;
    for (unsigned i = 0, k = n; i < k; ++i, --k) {
        for (unsigned j = i + 1; j < k; ++j)
            e.emplace_back(1 + i, 1 + j);
    }

    std::cout << e.size() << '\n';
    for (const auto& p : e)
        std::cout << p.first << ' ' << p.second << '\n';

    return 0;
}
