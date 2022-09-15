#include <iostream>
#include <vector>

const char* solve(const std::vector<std::vector<size_t>>& r, const std::vector<unsigned>& s)
{
    const size_t n = s.size();

    std::vector<bool> v(n);
    for (const unsigned x : s) {
        for (const size_t p : r[x-1]) {
            if (!v[p])
                return "NO";
        }
        v[x-1] = true;
    }

    return "YES";
}

int main()
{
    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<size_t>> r(n);
    for (size_t i = 0; i < m; ++i) {
        unsigned s, u;
        std::cin >> s >> u;

        r[u-1].push_back(s-1);
    }

    std::vector<unsigned> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i];
    
    std::cout << solve(r, s) << '\n';

    return 0;
}
