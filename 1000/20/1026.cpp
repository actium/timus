#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::string x;
    std::cin >> x;

    std::sort(a.begin(), a.end());

    size_t k;
    for (std::cin >> k; k != 0; --k) {
        unsigned x;
        std::cin >> x;

        std::cout << a[x-1] << '\n';
    }

    return 0;
}
