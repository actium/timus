#include <iostream>
#include <string>

using integer = unsigned long long;

integer search(const std::string& t, size_t x, char p)
{
    if (--x == 0)
        return t[x] != p;

    if (t[x] == p)
        return search(t, x, p);

    return (1ull << x) + search(t, x, 'A' ^ 'B' ^ 'C' ^ p ^ t[x]);
}

int main()
{
    unsigned n;
    std::cin >> n;

    std::string t;
    std::cin >> t;

    std::cout << search(t, n, 'A') << '\n';

    return 0;
}
