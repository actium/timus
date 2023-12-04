#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using integer = unsigned long long;

constexpr integer base = 1597, modulus = 1000000007;

integer powers[101];

void initialize_hashing()
{
    powers[0] = 1;
    for (size_t i = 1; i < 101; ++i)
        powers[i] = powers[i-1] * base % modulus;
}

integer hash(std::string_view s)
{
    const size_t n = s.length();

    integer h = 0;
    for (size_t i = 0; i < n; ++i)
        h += (s[i] - 'a' + 1) * powers[n - (i + 1)] % modulus;

    return h;
}

void solve(const std::vector<std::string>& s, size_t k, std::vector<std::string_view>& t)
{
    const size_t n = s.size();

    std::vector<std::vector<std::string_view>> p(n);
    for (size_t i = 0; i < n; ++i) {
        const size_t m = s[i].length();
        for (size_t j = 0; j + k <= m; ++j)
            p[i].emplace_back(s[i].data() + j, k);

        std::sort(p[i].begin(), p[i].end());
        p[i].erase(std::unique(p[i].begin(), p[i].end()), p[i].end());
    }

    std::vector<integer> hashes;
    for (size_t i = 0; i < n; ++i) {
        for (const std::string_view& x : p[i])
            hashes.push_back(hash(x));
    }

    std::sort(hashes.begin(), hashes.end());

    for (size_t i = 0; i < n; ++i) {
        if (k >= t[i].length())
            continue;

        for (const std::string_view& x : p[i]) {
            const integer h = hash(x);
            const auto it = std::next(std::lower_bound(hashes.begin(), hashes.end(), h));
            if (it == hashes.end() || *it != h) {
                t[i] = x;
                break;
            }
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::string> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i];

    std::vector<std::string_view> t(n);
    for (size_t i = 0; i < n; ++i)
        t[i] = s[i];

    initialize_hashing();

    for (size_t k = 1; k <= 100; ++k)
        solve(s, k, t);

    for (size_t i = 0; i < n; ++i)
        std::cout << t[i] << '\n';

    return 0;
}
