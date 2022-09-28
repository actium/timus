#include <algorithm>
#include <iostream>
#include <vector>

struct Link {
    unsigned s;
    unsigned t;
    unsigned d;
};

size_t resolve(std::vector<size_t>& roots, size_t x)
{
    size_t root = x;
    while (root != roots[root])
        root = roots[root];

    while (roots[x] != root)
        x = std::exchange(roots[x], root);

    return root;
}

size_t merge(std::vector<size_t>& roots, size_t x, size_t y)
{
    const size_t rx = resolve(roots, x), ry = resolve(roots, y);
    if (rx != ry) {
        roots[rx] = ry;
        return 1;
    }
    return 0;
}

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    std::vector<Link> links(m);
    for (Link& link : links)
        std::cin >> link.s >> link.t >> link.d;

    std::sort(links.begin(), links.end(), [](const Link& a, const Link& b) { return a.d < b.d; });

    std::vector<size_t> roots(n);
    for (size_t i = 0; i < n; ++i)
        roots[i] = i;

    std::vector<Link> plan;
    for (const Link& link : links) {
        plan.push_back(link);
        n -= merge(roots, link.s - 1, link.t - 1);
        if (n == 1)
            break;
    }

    std::cout << plan.back().d << '\n';
    std::cout << plan.size() << '\n';
    for (const Link& link : plan)
        std::cout << link.s << ' ' << link.t << '\n';

    return 0;
}
