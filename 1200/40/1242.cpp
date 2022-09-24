#include <algorithm>
#include <iostream>
#include <vector>

void filter(const std::vector<std::vector<size_t>>& g, size_t x, std::vector<bool>& c)
{
    c[x] = true;

    for (const size_t y : g[x])
        filter(g, y, c);
}

int main()
{
    size_t n;
    std::cin >> n >> std::ws;

    std::vector<std::vector<size_t>> a(n), s(n);
    for (std::string b; std::getline(std::cin, b) && b != "BLOOD"; ) {
        const size_t x = b.find(' ');

        const unsigned p = std::stoi(b.substr(x+1)), c = std::stoi(b.substr(0, x));
        a[c-1].push_back(p-1);
        s[p-1].push_back(c-1);
    }

    std::vector<bool> c(n);
    for (unsigned x; std::cin >> x; ) {
        filter(a, x-1, c);
        filter(s, x-1, c);
    }

    std::vector<size_t> r;
    for (size_t i = 0; i < n; ++i) {
        if (!c[i])
            r.push_back(i);
    }

    std:sort(r.begin(), r.end());

    for (const size_t x : r)
        std::cout << 1+x << ' ';

    if (r.empty())
        std::cout << 0 << '\n';

    return 0;
}
