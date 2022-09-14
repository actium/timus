#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    std::vector<unsigned> v;
    while (n > 3) {
        const unsigned d = (n + 1) / 2;
        v.push_back(d);
        n = std::max(d, n - d);
    }
    while (n > 1) {
        v.push_back(1);
        --n;
    }

    std::cout << v.size() << '\n';
    for (const unsigned x : v)
        std::cout << x << ' ';

    return 0;
}
