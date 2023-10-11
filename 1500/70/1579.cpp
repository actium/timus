#include <iostream>
#include <vector>

void solve(const std::vector<unsigned>& s, unsigned r)
{
    const size_t n = s.size();

    std::vector<std::vector<size_t>> p(1);
    {
        std::vector<bool> v(n);

        const auto insert = [&](size_t i) {
            p.back().push_back(i);
            v[i] = i;
        };

        insert(0);
        for (size_t i = 1; i < n; ++i) {
            if (s[i] > s[p.back().back()] + r)
                insert(i);
        }

        for (size_t k = p[0].size(); k < n; k += p.back().size()) {
            const size_t x = p.size() - 1;

            p.emplace_back();
            for (size_t i = 0, j = p[x][0] + 1; j < n; ++j) {
                if (v[j] || (!p.back().empty() && s[j] <= s[p.back().back()] + r))
                    continue;

                insert(j);

                while (i < p[x].size() && p[x][i] <= j)
                    ++i;

                j = (i < p[x].size() ? p[x][i] : n);
            }
        }
    }

    std::cout << p.size() << '\n';
    for (const std::vector<size_t>& v : p) {
        std::cout << v.size();
        for (const unsigned x : v)
            std::cout << ' ' << 1 + x;
        std::cout << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    unsigned r;
    std::cin >> r;

    std::vector<unsigned> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i];

    solve(s, r);

    return 0;
}
