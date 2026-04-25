#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

bool check(std::vector<unsigned> c, std::vector<unsigned> p)
{
    size_t x = 0;
    while (x < c.size() && x < p.size()) {
        if (c[x] > p[x]) {
            c.push_back(p[x]);
            c.push_back(c[x]);
        }
        if (c[x] < p[x]) {
            p.push_back(c[x]);
            p.push_back(p[x]);
        }
        ++x;
    }
    return x < p.size();
}

void answer(const std::vector<unsigned>& v)
{
    std::cout << "YES" << '\n';

    const char* separator = "";
    for (const unsigned x : v) {
        std::cout << separator << x;
        separator = " ";
    }
    std::cout << '\n';
}

void no_answer()
{
    std::cout << "NO" << '\n';
}

void solve(const std::vector<unsigned>& c)
{
    const size_t n = c.size();

    std::vector<unsigned> p(n);
    for (size_t i = 0; i < n; ++i)
        p[i] = 1 + i;

    if (n > 4) {
        // actually there is a simple deterministic algorithm:
        //   1. set p[i] = c[i] for every i with c[i] > 5
        //   2. brute-force the rest
        std::mt19937 rng(time(nullptr));
        while (!check(c, p))
            std::shuffle(p.begin(), p.end(), rng);

        return answer(p);
    }

    do {
        if (check(c, p))
            return answer(p);
    } while (std::next_permutation(p.begin(), p.end()));

    no_answer();
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> c(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> c[i];

    solve(c);

    return 0;
}
