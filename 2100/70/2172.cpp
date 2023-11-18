#include <iostream>
#include <vector>

void solve(std::vector<unsigned>& q, unsigned k)
{
    const size_t n = q.size();

    unsigned s = 0, m = 0;
    for (const unsigned x : q) {
        s += x;
        m = std::max(m, x);
    }

    m = std::max(m, (s + k - 1) / k);

    std::vector<std::vector<unsigned>> p(m);
    for (size_t i = 0, j = 0; i < n; ++i) {
        while (q[i]-- != 0)
            p[j++ % m].push_back(i + 1);
    }

    std::cout << m << '\n';
    for (const std::vector<unsigned>& v : p) {
        std::cout << v.size();
        for (const unsigned x : v)
            std::cout << ' ' << x;
        std::cout << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    unsigned k;
    std::cin >> k;

    std::vector<unsigned> q(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> q[i];

    solve(q, k);

    return 0;
}
