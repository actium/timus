#include <iostream>
#include <vector>

void assign(const std::vector<std::vector<size_t>>& g, size_t i, unsigned c, std::vector<unsigned>& a)
{
    if (a[i] != 0)
        return;

    a[i] = c;

    for (const size_t j : g[i])
        assign(g, j, c ^ 3, a);
}

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<std::vector<size_t>> g(n);
    for (size_t i = 0; i < n; ++i) {
        unsigned x;
        std::cin >> x;

        if (x != 0)
            g[x-1].push_back(i--);
    }

    for (size_t i = 0; i < n; ++i) {
        if (g[i].empty()) {
            std::cout << 0 << '\n';
            return 0;
        }
    }

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        assign(g, i, 1, a);

    std::vector<size_t> s;
    for (size_t i = 0; i < n; ++i) {
        if (a[i] == 1)
            s.push_back(i);
    }

    std::cout << s.size() << '\n';
    for (const size_t x : s)
        std::cout << 1+x << ' ';

    return 0;
}
