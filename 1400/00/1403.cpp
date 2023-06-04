#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

struct Container {
    unsigned x;
    unsigned t;
    unsigned v;
};

bool operator <(const Container& lhs, const Container& rhs)
{
    return lhs.t < rhs.t;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Container> cs(n);
    for (size_t i = 0; i < n; ++i) {
        cs[i].x = i + 1;
        std::cin >> cs[i].t >> cs[i].v;
    }

    std::sort(cs.begin(), cs.end());

    std::set<std::pair<unsigned, size_t>> s;
    for (size_t i = 0; i < n; ++i) {
        if (cs[i].t <= s.size() && cs[i].v > s.begin()->first)
            s.erase(s.begin());

        if (cs[i].t > s.size())
            s.emplace(cs[i].v, i);
    }

    std::vector<size_t> rs;
    for (const std::pair<unsigned, size_t>& x : s)
        rs.push_back(x.second);

    std::sort(rs.begin(), rs.end(), [&](size_t i, size_t j) { return cs[i].t < cs[j].t; });

    std::cout << rs.size() << '\n';
    for (const size_t i : rs)
        std::cout << cs[i].x << ' ';

    return 0;
}
