#include <iostream>
#include <set>
#include <utility>
#include <vector>

constexpr unsigned S = 100000;

struct State {
    unsigned f[S+1] = {};
    std::set<std::pair<unsigned, unsigned>> q;

    void insert(unsigned c)
    {
        if (f[c] != 0)
            q.erase(std::make_pair(f[c], c));

        q.emplace(++f[c], c);
    }

    void remove(unsigned c)
    {
        q.erase(std::make_pair(f[c], c));

        if (--f[c] != 0)
            q.emplace(f[c], c);
    }
};

void restore(std::vector<unsigned>& s, const std::vector<unsigned>& p)
{
    const size_t n = s.size(), m = p.size();

    State state;
    for (size_t i = 0; i < n; ++i) {
        if (i < m)
            state.insert(p[i]);

        if (s[i] == 0)
            s[i] = state.q.rbegin()->second;

        if (i + m >= n)
            state.remove(p[i+m-n]);
    }
}

void restore(const std::vector<unsigned>& s, std::vector<unsigned>& p)
{
    const size_t n = s.size(), m = p.size(), w = n - m + 1;

    State state;
    for (size_t i = 0; i < w; ++i)
        state.insert(s[i]);

    for (size_t i = 0; i < m; ++i) {
        if (p[i] == 0)
            p[i] = state.q.rbegin()->second;

        if (i + w < n) {
            state.remove(s[i]);
            state.insert(s[i+w]);
        }
    }
}

void solve(std::vector<unsigned>& s, std::vector<unsigned>& p)
{
    for (size_t i = 0, n = s.size(); i < n; ++i) {
        if (s[i] == 0)
            restore(s, std::as_const(p));

        std::cout << s[i] << " \n"[i+1==n];
    }

    for (size_t i = 0, m = p.size(); i < m; ++i) {
        if (p[i] == 0)
            restore(std::as_const(s), p);

        std::cout << p[i] << " \n"[i+1==m];
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i];

    size_t m;
    std::cin >> m;

    std::vector<unsigned> p(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> p[i];

    solve(s, p);

    return 0;
}
