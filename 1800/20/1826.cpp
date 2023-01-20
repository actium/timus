#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::sort(a.begin(), a.end());

    unsigned d = 0;
    for (size_t k = a.size(); k > 2; k -= 2) {
        const unsigned c1 = a[1] + a[0] + a[k-1] + a[1];
        const unsigned c2 = a[k-1] + a[0] + a[k-2] + a[0];
        d += std::min(c1, c2);

        a.pop_back();
        a.pop_back();
    }
    d += (a.size() == 2 ? a.back() : -a.back());

    std::cout << d << '\n';

    return 0;
}
