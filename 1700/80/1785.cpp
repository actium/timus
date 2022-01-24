#include <algorithm>
#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    const unsigned t[] = { 5, 10, 20, 50, 100, 250, 500, 1000, 2001 };
    const size_t x = std::upper_bound(std::begin(t), std::end(t), n) - std::begin(t);

    const char* s[] = { "few", "several", "pack", "lots", "horde", "throng", "swarm", "zounds", "legion" };
    std::cout << s[x] << '\n';

    return 0;
}
