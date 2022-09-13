#include <iostream>
#include <vector>

void solve(const std::vector<unsigned>& a, std::vector<std::vector<unsigned>>& c)
{
    const size_t n = c.size();

    for (const unsigned u : a) {
        for (const unsigned v : a)
            c[u-1][v-1] = 0;
    }

    std::vector<unsigned> w(n);
    for (size_t i = 1; i < n; ++i)
        w[i] = ~0u;

    std::vector<bool> v(n);
    for (size_t i = 0; i < n; ++i) {
        size_t x = n;
        for (size_t j = 0; j < n; ++j) {
            if (!v[j] && (x == n || w[j] < w[x]))
                x = j;
        }

        v[x] = true;

        for (size_t j = 0; j < n; ++j) {
            if (!v[j] && c[x][j] < w[j])
                w[j] = c[x][j];
        }
    }

    unsigned s = 0;
    for (const unsigned x : w)
        s += x;

    std::cout << s << '\n';
}

int main()
{
    size_t n, k;
    std::cin >> n >> k;

    std::vector<unsigned> a(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> a[i];

    std::vector<std::vector<unsigned>> c(n, std::vector<unsigned>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j)
            std::cin >> c[i][j];
    }

    solve(a, c);

    return 0;
}
