#include <iostream>
#include <numeric>
#include <vector>

#include <cassert>

void no_solution()
{
    std::cout << "No solution" << '\n';
}

void solve(const std::vector<std::string>& as, const std::vector<std::pair<unsigned, unsigned>>& ps)
{
    const size_t n = as.size();
    assert(ps.size() == n);

    unsigned x = 0;
    for (const auto& [p, q] : ps)
        x = std::max(x, q);

    if (__builtin_popcount(x) != 1)
        return no_solution();

    std::vector<unsigned> cs;
    for (const auto& [p, q] : ps)
        cs.push_back(p * x / q);

    if (std::accumulate(cs.begin(), cs.end(), 0u) != x)
        return no_solution();

    std::vector<std::pair<unsigned, unsigned>> tree;
    for (size_t i = 0; i < n; ++i)
        tree.insert(tree.end(), cs[i], std::make_pair(i, i));

    for (size_t i = 1; i < tree.size(); i += 2)
        tree.emplace_back(i, i + 1);

    std::cout << tree.size() << '\n';
    for (const auto& [u, v] : tree) {
        if (u == v)
            std::cout << as[u] << '\n';
        else
            std::cout << u << ' ' << v << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string b;
    std::cin >> b;

    std::vector<std::string> as;
    {
        size_t p = 0;
        for (size_t x = b.find('-'); x != std::string::npos; x = b.find('-', p)) {
            as.push_back(b.substr(p, x - p));
            p = x + 1;
        }
        as.push_back(b.substr(p));
    }

    const size_t n = as.size();

    std::vector<std::pair<unsigned, unsigned>> ps;
    for (size_t i = 0; i < n; ++i) {
        std::string p;
        std::cin >> p;

        const size_t x = p.find('/');
        assert(x != std::string::npos);

        const auto numerator = std::stoi(p.substr(0, x));
        const auto denominator = std::stoi(p.substr(x+1));
        const auto g = std::gcd(numerator, denominator);

        ps.emplace_back(numerator / g, denominator / g);
    }

    solve(as, ps);

    return 0;
}
