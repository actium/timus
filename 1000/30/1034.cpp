#include <iostream>
#include <vector>

size_t distance(size_t s, size_t t)
{
    return std::max(s, t) - std::min(s, t);
}

bool test(std::vector<size_t>& p, size_t i, size_t j, size_t k)
{
    for (const auto x : { i, j, k }) {
        for (size_t r = 0; r < p.size(); ++r) {
            if (r != x && distance(r, x) == distance(p[r], p[x]))
                return false;
        }
    }
    return true;
}

unsigned solve(std::vector<size_t>& p)
{
    const size_t n = p.size();

    unsigned q = 0;
    for (size_t i = 2; i < n; ++i) {
        const size_t pi = p[i];
        for (size_t j = 1; j < i; ++j) {
            const size_t pj = p[j];
            for (size_t k = 0; k < j; ++k) {
                const size_t pk = p[k];

                p[i] = pj; p[j] = pk; p[k] = pi;
                q += test(p, i, j, k);

                p[i] = pk; p[j] = pi; p[k] = pj;
                q += test(p, i, j, k);

                p[k] = pk;
            }
            p[j] = pj;
        }
        p[i] = pi;
    }
    return q;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<size_t> p(n);
    for (size_t i = 0; i < n; ++i) {
        unsigned r, c;
        std::cin >> r >> c;

        p[r-1] = c-1;
    }

    std::cout << solve(p) << '\n';

    return 0;
}
