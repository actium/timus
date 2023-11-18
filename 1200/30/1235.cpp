#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

void solve(unsigned w, unsigned h, const std::set<unsigned>& t)
{
    unsigned l = 1, p = 0, q = 0;

    std::vector<unsigned> dp[2];
    for (size_t i = 0; i < 2; ++i)
        dp[i].assign(w, 1);

    for (unsigned i = 1, x = 0; i < h; ++i, x ^= 1) {
        for (unsigned j = 1; j < w; ++j) {
            if (t.count(i * w + j) == 1)
                dp[x][j] = 1;
            else
                dp[x][j] = std::min({dp[x^1][j-1], dp[x^1][j], dp[x][j-1]}) + 1;

            if (dp[x][j] > l) {
                l = dp[x][j];
                p = j - l + 1;
                q = i - l + 1;
            }
        }
    }

    std::cout << p << ' ' << q << ' ' << l << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    unsigned w, h;
    std::cin >> w >> h;

    std::set<unsigned> t;
    for (size_t i = 0; i < n; ++i) {
        unsigned x, y;
        std::cin >> x >> y;

        t.insert(y * w + x);
    }

    solve(w, h, t);

    return 0;
}
