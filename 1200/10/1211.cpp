#include <iostream>
#include <utility>
#include <vector>

const char* solve(const std::vector<unsigned>& p)
{
    const size_t n = p.size();

    std::vector<size_t> r(n);
    for (size_t i = 0; i < n; ++i)
        r[i] = i;

    const auto resolve = [&r](size_t x) {
        size_t root = x;
        while (root != r[root])
            root = r[root];

        while (r[x] != root)
            x = std::exchange(r[x], root);

        return root;
    };

    size_t k = n;
    for (size_t i = 0; i < n; ++i) {
        if (p[i] == 0)
            continue;

        const size_t u = resolve(i), v = resolve(p[i] - 1);
        if (u == v)
            return "NO";

        r[u] = v;
        --k;
    }
    return k == 1 ? "YES" : "NO";
}

void test_case()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> p(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> p[i];

    std::cout << solve(p) << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t t;
    std::cin >> t;

    while (t-- > 0)
        test_case();

    return 0;
}
