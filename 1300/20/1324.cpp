#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned q;
    std::cin >> q;

    std::vector<unsigned> p;
    if (q > 1) {
        p.push_back(2);
        for (unsigned x = 2, k = 2; k < q; x = x * (x + 1) / 2, k = (x - 1) * 2)
            p.push_back(x);
    }

    std::cout << p.size() << '\n';
    for (auto it = p.rbegin(); it != p.rend(); ++it)
        std::cout << *it << '\n';

    return 0;
}
