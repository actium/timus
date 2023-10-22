#include <iostream>
#include <queue>
#include <string>
#include <vector>

template <typename F>
void paint(std::vector<std::string>& g, size_t r, size_t c, char t, F&& callback)
{
    const char s = g[r][c];

    std::queue<std::pair<size_t, size_t>> q;

    const auto enqueue = [&](size_t r, size_t c) {
        if (r < g.size() && c < g[0].length() && g[r][c] == s) {
            g[r][c] = t;
            q.emplace(r, c);
        }
    };

    enqueue(r, c);
    while (!q.empty()) {
        const std::pair<size_t, size_t> x = q.front();
        q.pop();

        enqueue(x.first - 1, x.second);
        enqueue(x.first, x.second + 1);
        enqueue(x.first + 1, x.second);
        enqueue(x.first, x.second - 1);

        callback();
    }
}

void solve(std::vector<std::string>& g, const std::vector<unsigned>& s)
{
    const size_t n = g.size(), m = g[0].length(), k = s.size();

    for (size_t i = 0; i < k; ++i) {
        if (i % 2 == 0) {
            paint(g, n-1, 0, '0' + s[i], [] {});
        } else {
            paint(g, 0, m-1, '0' + s[i], [] {});
        }
    }

    unsigned a = 0;
    paint(g, n-1, 0, 'A', [&a] { ++a; });
    std::cout << a << '\n';

    unsigned b = 0;
    paint(g, 0, m-1, 'B', [&b] { ++b; });
    std::cout << b << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::string> g(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> g[i];

    size_t k;
    std::cin >> k;

    std::vector<unsigned> s(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> s[i];

    solve(g, s);

    return 0;
}
