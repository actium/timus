#include <iostream>
#include <set>
#include <string>
#include <vector>

void filter(std::vector<std::string>& t)
{
    size_t k = 0;

    std::set<std::string> s;
    for (const std::string& x : t) {
        std::string c = x;

        const size_t p = c.rfind(" #");
        if (p != std::string::npos)
            c.resize(p);

        if (s.insert(c).second)
            t[k++] = x;
    }

    t.resize(k);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned y, n, q;
    std::cin >> y >> n >> q >> std::ws;

    std::vector<std::string> t(n);
    for (std::string& x : t)
        std::getline(std::cin, x);

    filter(t);

    std::cout << t[q] << '\n';

    return 0;
}
