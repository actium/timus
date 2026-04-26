#include <iostream>
#include <vector>

unsigned solve(unsigned g, unsigned w, unsigned b, unsigned p, const std::vector<unsigned>& xs)
{
    std::vector<unsigned> s(1+g);
    for (const unsigned x : xs) {
        const unsigned lb1 = (x > p-1 ? x - (p-1) : 0), ub1 = x+w;
        const unsigned lb2 = (x > b-1 ? x - (b-1) : 0), ub2 = (x+w > b-p ? x+w - (b-p) : 0);

        if (lb1 < ub2) {
            ++s[lb2];
            --s[ub1];
        } else {
            ++s[lb2];
            --s[ub2];
            ++s[lb1];
            --s[ub1];
        }
    }

    std::pair<unsigned, unsigned> best = { s[0], 0 };
    for (unsigned x = 1; x + b <= g; ++x) {
        s[x] += s[x-1];
        best = std::min(best, std::make_pair(s[x], x));
    }
    return best.second;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned g, w;
    std::cin >> g >> w;

    unsigned b, p;
    std::cin >> b >> p;

    size_t n;
    std::cin >> n;

    std::vector<unsigned> xs(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> xs[i];

    std::cout << solve(g, w, b, p, xs) << '\n';

    return 0;
}
