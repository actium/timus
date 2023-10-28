#include <algorithm>
#include <iostream>
#include <vector>

void print_answer(const std::vector<unsigned>& s, unsigned b, unsigned d, unsigned k)
{
    const size_t n = s.size();

    std::vector<uint16_t> o(n);
    for (size_t i = 0; i < n; ++i)
        o[i] = i;

    std::sort(o.begin(), o.end(), [&](size_t i, size_t j) {
        return s[i] < s[j];
    });

    std::cout << k << '\n';
    for (size_t i = 0, j = 0; i < k; ++i) {
        while (s[o[j]] != b + i * d)
            ++j;

        std::cout << 1 + o[j] << ' ';
    }
}

void solve(const std::vector<unsigned>& s)
{
    std::vector<unsigned> a(s.begin(), s.end());

    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());

    const size_t n = a.size();
    if (n == 1) {
        print_answer(s, a[0], 0, 1);
        return;
    }

    std::pair<size_t, size_t> x = { 0, 1 };

    std::vector<std::vector<uint16_t>> dp(n, std::vector<uint16_t>(n, 2));
    for (size_t j = n - 2; j > 0; --j) {
        for (size_t i = j - 1, k = j + 1; ~i != 0 && k < n;) {
            if (a[i] + a[k] < 2 * a[j]) {
                ++k;
                continue;
            }
            if (a[i] + a[k] > 2 * a[j]) {
                --i;
                continue;
            }

            dp[i][j] = dp[j][k] + 1;

            if (dp[i][j] > dp[x.first][x.second]) {
                x.first = i;
                x.second = j;
            }

            --i, ++k;
        }
    }

    print_answer(s, a[x.first], a[x.second] - a[x.first], dp[x.first][x.second]);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i];

    solve(s);

    return 0;
}
