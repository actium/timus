#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using integer = unsigned long long;
using WP = std::pair<integer, integer>;

struct Candidate {
    size_t i;
    WP wp;
    integer d;
};

bool operator <(const Candidate& lhs, const Candidate& rhs)
{
    return lhs.d < rhs.d;
}

void solve(std::vector<WP>& ps, size_t k, WP max, unsigned a, unsigned b)
{
    const size_t n = ps.size();

    const auto evaluate = [&](WP wp) {
        integer t = 0;
        if (wp.first > max.first)
            t += (wp.first - max.first) * a * 100;
        if (wp.second > max.second)
            t += (wp.second - max.second) * b;

        return t;
    };

    std::vector<Candidate> cs(n);
    for (size_t i = 0; i < n; ++i) {
        cs[i] = { i, ps[i], 0 };

        auto w = std::to_string(ps[i].first);
        if (const auto x = w.find_first_not_of('9'); x != std::string::npos) {
            w[x] = '9';

            WP wp = ps[i];
            wp.first = std::stoull(w);
            cs[i] = std::max(cs[i], { i, wp, evaluate(wp) - evaluate(ps[i]) });
        }

        auto p = std::to_string(ps[i].second);
        if (const auto x = p.find_first_not_of('9'); x != std::string::npos) {
            p[x] = '9';

            WP wp = ps[i];
            wp.second = std::stoull(p);
            cs[i] = std::max(cs[i], { i, wp, evaluate(wp) - evaluate(ps[i]) });
        }
    }

    std::sort(cs.rbegin(), cs.rend());

    for (size_t i = 0; i < k; ++i)
        ps[cs[i].i] = cs[i].wp;

    integer t = 0;
    for (size_t i = 0; i < n; ++i)
        t += evaluate(ps[i]);

    std::cout << std::fixed << t / 100.0 << '\n';
    for (size_t i = 0; i < n; ++i)
        std::cout << ps[i].first << ' ' << ps[i].second << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, k;
    std::cin >> n >> k;

    WP max;
    std::cin >> max.first >> max.second;

    unsigned a, b;
    std::cin >> a >> b;

    std::vector<WP> ps(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> ps[i].first >> ps[i].second;

    solve(ps, k, max, a, b);

    return 0;
}
