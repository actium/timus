#include <array>
#include <iostream>
#include <string>
#include <vector>

constexpr unsigned oo = ~0u >> 1;

struct Dish {
    std::string s;
    unsigned c;
    unsigned v;
};

struct State {
    unsigned c = oo;
    unsigned k = 0;
    std::array<unsigned, 100> f = {};
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    unsigned m;
    std::cin >> m;
    m *= 1000;

    std::vector<Dish> dishes(n);
    for (size_t i = 0; i < n; ++i) {
        double v;
        std::cin >> dishes[i].s >> dishes[i].c >> v;
        dishes[i].v = v * 1000 + 0.5;
    }

    std::vector<State> dp(m + 10000);
    dp[0].c = 0;
    for (size_t i = 0; i < n; ++i) {
        const unsigned dc = dishes[i].c, dv = dishes[i].v;

        for (unsigned j = 0; j < m; ++j) {
            const unsigned k = dp[j].k + (dp[j].f[i] == 0);
            if (dp[j].c + dc < dp[j+dv].c || dp[j].c + dc == dp[j+dv].c && k > dp[j+dv].k) {
                dp[j+dv].c = dp[j].c + dc;
                dp[j+dv].k = k;
                dp[j+dv].f = dp[j].f;
                ++dp[j+dv].f[i];
            }
        }
    }

    unsigned x = 0;
    for (unsigned i = 1; i < 10000; ++i) {
        if (dp[m+i].c < dp[m+x].c || dp[m+i].c == dp[m+x].c && dp[m+i].k > dp[m+x].k)
            x = i;
    }

    std::cout << dp[m+x].c << '\n';
    for (size_t i = 0; i < n; ++i) {
        if (dp[m+x].f[i] != 0)
            std::cout << dishes[i].s << ' ' << dp[m+x].f[i] << '\n';
    }

    return 0;
}
