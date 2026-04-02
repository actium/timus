#include <iostream>
#include <numeric>
#include <vector>

unsigned T(unsigned n)
{
    return n * (n - 1) / 2;
}

void print_edge(unsigned u, unsigned v)
{
    std::cout << u << ' ' << v << '\n';
}

bool search(unsigned n, unsigned d, std::vector<unsigned>& p)
{
    if (d == 0)
        return std::accumulate(p.begin(), p.end(), 0) <= n;

    if (p.size() == 4)
        return false;

    for (unsigned b = 3, c = T(b); c <= d; c = T(++b)) {
        p.push_back(b);
        if (search(n, d - c, p))
            return true;

        p.pop_back();
    }
    return false;
}

void solve(unsigned n, unsigned k)
{
    if (std::vector<unsigned> p; search(n, T(n) - k, p)) {
        unsigned v = 1;
        for (unsigned c : p)
            for (print_edge(v, v+c-1); c-- != 0 && ++v <= n; print_edge(v-1, v));

        for (unsigned u = v + 1; u <= n; ++u)
            print_edge(v, u);
    } else {
        std::cout << -1 << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n, k;
    std::cin >> n >> k;

    solve(n, k);

    return 0;
}
