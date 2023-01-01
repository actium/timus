#include <iostream>
#include <vector>

const char* solve(unsigned l, const std::vector<unsigned>& k)
{
    for (const unsigned p : k) {
        if (l < p)
            return "YES";

        l -= l % p;
    }
    return "NO";
}

int main()
{
    unsigned l;
    std::cin >> l;

    size_t n;
    std::cin >> n;

    std::vector<unsigned> k(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> k[i];

    std::cout << solve(l, k) << '\n';

    return 0;
}
