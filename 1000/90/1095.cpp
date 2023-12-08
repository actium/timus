#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

constexpr unsigned t[24] = {
    1, 3, 2, 6, 4, 5, 1, 3, 2, 6, 4, 5, 1, 3, 2, 6, 4, 5, 1, 3, 2, 6, 4, 5,
};

std::array<std::string, 7> search(const std::string& s, size_t lb, size_t ub)
{
    const size_t n = ub - lb;

    std::array<std::string, 7> c;
    if (n > 7) {
        const size_t m = (lb + ub) / 2;

        const std::array<std::string, 7> lhs = search(s, lb, m);
        const std::array<std::string, 7> rhs = search(s, m, ub);

        for (size_t i = 0; i < 7; ++i) {
            if (lhs[i].empty())
                continue;

            for (size_t j = 0; j < 7; ++j) {
                if (!rhs[j].empty())
                    c[(i + j) % 7] = lhs[i] + rhs[j];
            }
        }
    } else {
        std::vector<size_t> p(n);
        for (size_t i = 0; i < n; ++i)
            p[i] = i;

        unsigned k = 0;
        do {
            unsigned r = 0;
            for (size_t i = 0; i < n; ++i)
                r += t[s.length()-1-(lb+i)] * (s[lb + p[i]] - '0');

            r %= 7;

            if (c[r].empty()) {
                for (size_t i = 0; i < n; ++i)
                    c[r].push_back(s[lb + p[i]]);

                ++k;
            }
        } while (k < 7 && std::next_permutation(p.begin(), p.end()));
    }
    return c;
}

std::string solve(const std::string& s)
{
    std::string t;
    std::copy_if(s.begin(), s.end(), std::back_inserter(t), [](char c) { return c != '0'; });

    const std::array<std::string, 7> c = search(t, 0, t.length());
    if (c[0].empty())
        return "0";

    return c[0] + std::string(s.length() - t.length(), '0');
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    for (unsigned i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;

        std::cout << solve(s) << '\n';
    }

    return 0;
}
