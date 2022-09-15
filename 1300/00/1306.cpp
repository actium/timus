#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    unsigned n;
    std::cin >> n;

    const unsigned k = n / 2 + 1;

    std::vector<unsigned> a(k);
    for (unsigned i = 0; i < k; ++i)
        std::cin >> a[i];

    std::make_heap(a.begin(), a.end());
    std::pop_heap(a.begin(), a.end());

    for (unsigned i = k; i < n; ++i) {
        unsigned x;
        std::cin >> x;

        if (x < a.back()) {
            a.back() = x;
            std::push_heap(a.begin(), a.end());
            std::pop_heap(a.begin(), a.end());
        }
    }

    if (n % 2 == 0) {
        const unsigned x = a[k-1];
        std::pop_heap(a.begin(), a.end() - 1);
        const unsigned y = a[k-2];

        std::cout << std::fixed << (x + y) / 2.0 << '\n';
    } else {
        std::cout << a.back() << '\n';
    }

    return 0;
}
