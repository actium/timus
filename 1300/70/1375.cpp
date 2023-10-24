#include <iostream>
#include <vector>

void solve(unsigned k, unsigned p)
{
    std::vector<unsigned> r(p, ~0u);
    for (unsigned i = 0; i < p; ++i) {
        const unsigned u = 1ull * i * i % p;
        r[u] = i;

        const unsigned v = (p + k - u) % p;
        if (r[v] != ~0u) {
            std::cout << i << ' ' << r[v] << '\n';
            return;
        }
    }

    std::cout << "NO SOLUTION" << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned k, p;
    std::cin >> k >> p;

    solve(k, p);

    return 0;
}
