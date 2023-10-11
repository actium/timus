#include <iostream>
#include <queue>
#include <string>
#include <vector>

unsigned parse(std::string& s)
{
    unsigned v = 0;
    for (size_t i = 0; i < 4; ++i) {
        const size_t x = s.rfind('.');
        if (x != std::string::npos) {
            v |= std::stoi(s.substr(x + 1)) << i * 8;
            s.resize(x);
        } else {
            v |= std::stoi(s) << i * 8;
        }
    }
    return v;
}

void solve(const std::vector<std::vector<unsigned>>& a, unsigned u, unsigned v)
{
    const size_t n = a.size();

    const auto check = [&](size_t i, size_t j) {
        for (const unsigned u : a[i]) {
            for (const unsigned v : a[j]) {
                if (u == v)
                    return true;
            }
        }
        return false;
    };

    std::vector<std::vector<size_t>> g(n);
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (check(i, j)) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    std::queue<size_t> q;
    std::vector<size_t> s(n, n);

    const auto enqueue = [&](size_t u, size_t p) {
        if (s[u] == n) {
            q.push(u);
            s[u] = p;
        }
    };

    enqueue(u - 1, v - 1);
    while (!q.empty() && q.front() != v - 1) {
        const size_t x = q.front();
        q.pop();

        for (const size_t y : g[x])
            enqueue(y, x);
    }

    if (!q.empty()) {
        std::vector<size_t> p;
        for (p.push_back(q.front()); p.back() != u - 1; p.push_back(s[p.back()]));

        std::cout << "Yes" << '\n';
        for (auto it = p.rbegin(); it != p.rend(); ++it)
            std::cout << 1 + *it << ' ';
    } else {
        std::cout << "No" << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::vector<unsigned>> a(n);
    for (size_t i = 0; i < n; ++i) {
        size_t k;
        std::cin >> k;

        a[i].resize(k);
        for (size_t j = 0; j < k; ++j) {
            std::string address, mask;
            std::cin >> address >> mask;

            a[i][j] = parse(address) & parse(mask);
        }
    }

    unsigned u, v;
    std::cin >> u >> v;

    solve(a, u, v);

    return 0;
}
