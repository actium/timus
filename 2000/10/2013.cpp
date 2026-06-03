#include <iostream>
#include <set>
#include <vector>

struct Bar {
    unsigned k;
    std::vector<unsigned> successors;
    std::set<unsigned> variants;
};

void solve(std::vector<Bar>& bars)
{
    std::vector<std::pair<size_t, unsigned>> q;

    const auto enqueue = [&](size_t bar, unsigned v) {
        if (bars[bar].variants.insert(v).second)
            q.emplace_back(bar, v);
    };

    enqueue(0, 0);
    while (!q.empty()) {
        const auto [bar, v] = q.back();
        q.pop_back();

        for (const auto s : bars[bar].successors)
            enqueue(s-1, bars[bar].k == 0 ? v : bars[bar].k);
    }

    for (const auto& bar : bars) {
        std::string p = "unknown";
        if (bar.variants.size() == 1) {
            const auto x = *bar.variants.begin();
            p = (x == 0 ? "sober" : std::to_string(x));
        }

        if (bar.k == 0)
            std::cout << p << ' ' << p << '\n';
        else
            std::cout << p << ' ' << bar.k << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Bar> bars(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> bars[i].k;

        size_t m;
        std::cin >> m;

        bars[i].successors.resize(m);
        for (size_t j = 0; j < m; ++j)
            std::cin >> bars[i].successors[j];
    }

    solve(bars);

    return 0;
}
