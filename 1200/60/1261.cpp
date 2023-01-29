#include <algorithm>
#include <iostream>

int main()
{
    unsigned s[65540] = { 0, 1 };
    for (unsigned i = 0; i < 32768; ++i) {
        s[2 * i + 2] = 3 * s[i + 1];
        s[2 * i + 3] = s[2 * i + 2] + 1;
    }

    unsigned n;
    std::cin >> n;

    auto it = std::upper_bound(std::begin(s), std::end(s), n);
    while (!std::binary_search(std::begin(s), it, *it - n))
        ++it;

    std::cout << *it << ' ' << *it - n << '\n';

    return 0;
}
