#include <iostream>
#include <unordered_set>
#include <vector>

void solve(const std::vector<std::vector<unsigned>>& b)
{
    const size_t n = b.size();

    std::unordered_set<size_t> q;

    std::vector<unsigned> c(n), d(n);
    for (size_t i = 0; i < n; ++i) {
        d[i] = b[i].size();

        if (d[i] > 1)
            q.insert(i);
    }

    size_t f[2] = { n, 0 };
    while (!q.empty()) {
        const size_t x = *q.begin();
        q.erase(q.begin());

        for (const unsigned u : b[x]) {
            if (c[u-1] == c[x]) {
                if (--d[u-1] == 1)
                    q.erase(u - 1);

                --d[x];
            } else {
                if (d[u-1]++ == 1)
                    q.insert(u - 1);

                ++d[x];
            }
        }

        --f[c[x]];
        c[x] ^= 1;
        ++f[c[x]];

        if (d[x] > 1)
            q.insert(x);
    }

    unsigned x = c[0] ^ 1;
    if (f[x] >= f[x^1])
        x ^= 1;

    std::cout << f[x] << '\n';
    for (size_t i = 0; i < n; ++i) {
        if (c[i] == x)
            std::cout << 1 + i << ' ';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::vector<unsigned>> b(n);
    for (size_t i = 0; i < n; ++i) {
        size_t m;
        std::cin >> m;

        b[i].resize(m);

        for (size_t j = 0; j < m; ++j)
            std::cin >> b[i][j];
    }

    solve(b);

    return 0;
}
