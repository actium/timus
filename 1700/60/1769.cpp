#include <bitset>
#include <iostream>
#include <string>

int main()
{
    std::string s;
    std::cin >> s;

    const size_t n = s.length();

    std::bitset<1000000> v;
    for (size_t i = 0; i < n; ++i) {
        unsigned x = 0;
        for (size_t j = 0, k = std::min<size_t>(n - i, 6); j < k; ++j) {
            x = x * 10 + s[i+j] - '0';
            v.set(x);
        }
    }

    unsigned x = 1;
    while (v.test(x))
        ++x;

    std::cout << x << '\n';

    return 0;
}
