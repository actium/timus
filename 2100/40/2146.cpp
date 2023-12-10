#include <algorithm>
#include <iostream>
#include <string>

std::pair<char, unsigned> most_frequent(const std::string& s, size_t x, size_t p)
{
    const size_t n = s.length(), q = n / p;

    unsigned f[26] = {};
    for (size_t i = 0; i < q; ++i)
        ++f[s[x + i * p] - 'a'];

    const auto it = std::max_element(std::begin(f), std::end(f));
    return std::make_pair('a' + it - std::begin(f), q - *it);
}

void solve(const std::string& s, size_t k)
{
    const size_t n = s.length();

    std::pair<unsigned, std::string> v = { n, s };
    for (size_t p = 1; p < n; ++p) {
        if (n % p != 0)
            continue;

        std::string t(p, ' ');
        unsigned q = 0;
        for (size_t i = 0; i < p && q <= k; ++i) {
            const std::pair<char, unsigned> c = most_frequent(s, i, p);
            t[i] = c.first;
            q += c.second;
        }

        if (q <= k) {
            v.first = p;
            v.second = t;
            break;
        }
    }

    std::cout << v.first << '\n';
    for (size_t i = 0; i < n; i += v.first)
        std::cout << v.second;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, k;
    std::cin >> n >> k;

    std::string s;
    std::cin >> s;

    solve(s, k);

    return 0;
}
