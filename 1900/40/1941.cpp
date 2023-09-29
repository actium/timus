#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

unsigned solve(const std::string& s, const std::string& t)
{
    const size_t n = s.length() / 4 + 1, m = t.length() / 4 + 1;

    unsigned q = 0;

    std::unordered_map<std::string_view, unsigned> x;
    {
        for (size_t i = 0; i < n; ++i) {
            const std::string_view key(s.data() + i * 4, 3);
            q += x.emplace(key, q).second;
        }
    }

    const auto lookup = [&](const char* p) {
        const auto it = x.find(std::string_view(p, 3));
        return it != x.end() ? it->second : ~0u;
    };

    std::vector<int> b(q);
    for (size_t i = 0; i < n; ++i)
        ++b[lookup(s.data() + i * 4)];

    unsigned k = 0;
    for (size_t i = 0, c = q; i < m; ++i) {
        if (i >= n) {
            const unsigned u = lookup(t.data() + (i - n) * 4);
            if (u != ~0u && b[u]++ == 0)
                ++c;
        }

        const unsigned u = lookup(t.data() + i * 4);
        if (u != ~0u && --b[u] == 0)
            --c;

        k += (c == 0);
    }
    return k;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s;
    std::getline(std::cin, s);

    std::string(t);
    std::getline(std::cin, t);

    std::cout << solve(s, t) << '\n';

    return 0;
}
