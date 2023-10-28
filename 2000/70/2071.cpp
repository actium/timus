#include <algorithm>
#include <iostream>
#include <vector>

unsigned evaluate(const std::vector<unsigned>& s)
{
    unsigned v = 0;
    for (unsigned i = 0; i < 3; ++i) {
        for (size_t x = 0; x < s.size(); ++x) {
            if ((s[x] & 1 << i) == 0)
                continue;

            ++v;

            while (x < s.size() && (s[x] & 1 << i) != 0)
                ++x;
        }
    }
    return v;
}

unsigned arrange(std::vector<unsigned>& s)
{
    std::sort(s.begin(), s.end());

    std::pair<unsigned, std::vector<unsigned>> v = { evaluate(s), s };
    while (std::next_permutation(s.begin(), s.end()))
        v = std::min(v, std::make_pair(evaluate(s), s));

    std::swap(s, v.second);
    return v.first;
}

void solve(const std::vector<unsigned>& a)
{
    const size_t n = a.size();

    std::vector<unsigned> x[8], s;
    {
        bool v[128] = {};
        for (size_t i = 0; i < n; ++i) {
            x[a[i]].push_back(1 + i);

            if (!v[a[i]])
                s.push_back(a[i]);

            v[a[i]] = true;
        }
    }

    std::cout << arrange(s) << '\n';
    for (const unsigned i : s) {
        for (const unsigned v : x[i])
            std::cout << v << ' ';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;

        for (const char c : s)
            a[i] |= 1 << (c == 'P' ? 2 : c - 'A');
    }

    solve(a);

    return 0;
}
