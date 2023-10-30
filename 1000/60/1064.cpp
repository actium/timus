#include <iostream>
#include <vector>

unsigned search(unsigned n, unsigned x)
{
    unsigned p = 0, q = n - 1, k = 0;
    while (p <= q) {
        const unsigned i = (p + q) / 2;
        ++k;
        if (i == x)
            return k;

        if (x < i)
            q = i - 1;
        else
            p = i + 1;
    }
    return ~0u;
}

int main()
{
    unsigned i, l;
    std::cin >> i >> l;

    std::vector<std::pair<unsigned, unsigned>> s;
    for (unsigned n = i + 1; n <= 10000; ++n) {
        if (search(n, i) != l)
            continue;

        if (s.empty() || n != s.back().second + 1)
            s.emplace_back(n, n);

        s.back().second = n;
    }

    std::cout << s.size() << '\n';
    for (const std::pair<unsigned, unsigned>& i : s)
        std::cout << i.first << ' ' << i.second << '\n';

    return 0;
}
