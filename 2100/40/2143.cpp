#include <iostream>
#include <string>
#include <vector>

constexpr char t[9] = { 'A', 'B', 'C', '|', '_', '|', 'D', 'E', 'F' };

void search(const std::vector<std::string>& a, size_t offset, std::vector<std::string>& s)
{
    const size_t n = a.size();

    std::vector<std::vector<std::pair<unsigned, unsigned>>> dp(n, std::vector<std::pair<unsigned, unsigned>>(5));
    if (a[0][offset+0] == '.')
        dp[0][1] = { 1, 0 };
    if (a[0][offset+1] == '.')
        dp[0][2] = { 1, 0 };
    if (a[0][offset+2] == '.')
        dp[0][3] = { 1, 0 };
    if (a[0][offset+0] == '.' && a[0][offset+2] == '.')
        dp[0][4] = { 2, 0 };

    for (size_t i = 1; i < n; ++i) {
        for (unsigned j = 0; j < 5; ++j) {
            if (dp[i-1][j].first > dp[i][0].first) {
                dp[i][0].first = dp[i-1][j].first;
                dp[i][0].second = j;
            }
        }

        if (a[i][offset+0] == '.') {
            dp[i][1] = { 1, 0 };
            if (dp[i-1][0].first >= dp[i][1].first) {
                dp[i][1].first = dp[i-1][0].first + 1;
                dp[i][1].second = 0;
            }
            if (dp[i-1][3].first >= dp[i][1].first) {
                dp[i][1].first = dp[i-1][3].first + 1;
                dp[i][1].second = 3;
            }
        }
        if (a[i][offset+1] == '.') {
            dp[i][2] = { 1, 0 };
            if (dp[i-1][0].first >= dp[i][2].first) {
                dp[i][2].first = dp[i-1][0].first + 1;
                dp[i][2].second = 0;
            }
        }
        if (a[i][offset+2] == '.') {
            dp[i][3] = { 1, 0 };
            if (dp[i-1][0].first >= dp[i][3].first) {
                dp[i][3].first = dp[i-1][0].first + 1;
                dp[i][3].second = 0;
            }
            if (dp[i-1][1].first >= dp[i][3].first) {
                dp[i][3].first = dp[i-1][1].first + 1;
                dp[i][3].second = 1;
            }
        }
        if (a[i][offset+0] == '.' && a[i][offset+2] == '.') {
            dp[i][4] = { 2, 0 };
            if (dp[i-1][0].first + 2 > dp[i][4].first) {
                dp[i][4].first = dp[i-1][0].first + 2;
                dp[i][4].second = 0;
            }
        }
    }

    unsigned x = 0;
    for (unsigned i = 1; i < 5; ++i) {
        if (dp[n-1][i].first > dp[n-1][x].first)
            x = i;
    }

    for (size_t i = n-1; ~i != 0; --i) {
        const std::string r = std::to_string(i+1);
        if (x == 1 || x == 4)
            s.push_back(r + t[offset+0]);
        if (x == 2)
            s.push_back(r + t[offset+1]);
        if (x == 3 || x == 4)
            s.push_back(r + t[offset+2]);

        x = dp[i][x].second;
    }
}

void solve(const std::vector<std::string>& a, size_t k)
{
    std::vector<std::string> q;
    search(a, 0, q);
    search(a, 6, q);

    if (q.size() < k) {
        std::cout << "PORAZHENIE" << '\n';
    } else {
        std::cout << "POBEDA" << '\n';
        for (size_t i = 0; i < k; ++i)
            std::cout << q[i] << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, k;
    std::cin >> n >> k;

    std::vector<std::string> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    solve(a, k);

    return 0;
}
