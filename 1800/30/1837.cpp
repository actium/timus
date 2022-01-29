#include <iostream>
#include <map>
#include <set>
#include <string>

using graph_t = std::map<std::string, std::set<std::string>>;

void traverse(const graph_t& g, const std::string& x, unsigned y, std::map<std::string, unsigned>& v)
{
    v[x] = y;

    const auto it = g.find(x);
    if (it == g.cend())
        return;

    for (const std::string& a : it->second) {
        const auto it = v.find(a);
        if (it == v.end() || y + 1 < it->second)
            traverse(g, a, y + 1, v);
    }
}

int main()
{
    unsigned n;
    std::cin >> n;

    graph_t g;
    while (n-- > 0) {
        std::string a, b, c;
        std::cin >> a >> b >> c;

        g[a].insert(b);
        g[a].insert(c);
        g[b].insert(a);
        g[b].insert(c);
        g[c].insert(a);
        g[c].insert(b);
    }

    std::map<std::string, unsigned> v;
    traverse(g, "Isenbaev", 0, v);

    for (const auto& e : g) {
        std::cout << e.first << ' ';

        const auto it = v.find(e.first);
        if (it == v.end())
            std::cout << "undefined" << '\n';
        else
            std::cout << it->second << '\n';
    }

    return 0;
}
