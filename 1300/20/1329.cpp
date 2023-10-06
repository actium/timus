#include <iostream>
#include <vector>

constexpr size_t N = 1 + 40000, M = 16;

unsigned depths[N];
std::vector<unsigned> jumps[N];

void prepare(const std::vector<std::vector<unsigned>>& t, size_t u, size_t p)
{
    depths[u] = depths[p] + 1;

    jumps[u].resize(M);
    jumps[u][0] = p;
    for (int i = 1; i < M; ++i)
        jumps[u][i] = jumps[jumps[u][i-1]][i-1];

    for (const unsigned v : t[u])
        prepare(t, v, u);
}

unsigned lca(unsigned u, unsigned v)
{
    if (depths[v] < depths[u])
        std::swap(v, u);

    for (int i = M - 1; i >= 0; --i) {
        if (depths[jumps[v][i]] >= depths[u])
            v = jumps[v][i];
    }

    if (v == u)
        return v;

    for (int i = M - 1; i >= 0; --i) {
        if (jumps[v][i] != jumps[u][i]) {
            v = jumps[v][i];
            u = jumps[u][i];
        }
    }
    return jumps[v][0];
}

void solve(const std::vector<std::pair<int, int>>& e, const std::vector<std::pair<size_t, size_t>>& q)
{
    std::vector<std::vector<unsigned>> t(N);

    size_t root = N;
    for (const std::pair<int, int>& x : e) {
        if (x.second != -1)
            t[x.second].push_back(x.first);
        else
            root = x.first;
    }

    prepare(t, root, root);

    for (const std::pair<size_t, size_t>& r : q) {
        const unsigned x = lca(r.first, r.second);
        if (x == r.first) {
            std::cout << '1' << '\n';
            continue;
        }
        if (x == r.second) {
            std::cout << '2' << '\n';
            continue;
        }
        std::cout << '0' << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::pair<int, int>> e(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> e[i].first >> e[i].second;

    size_t k;
    std::cin >> k;

    std::vector<std::pair<size_t, size_t>> q(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> q[i].first >> q[i].second;

    solve(e, q);

    return 0;
}
