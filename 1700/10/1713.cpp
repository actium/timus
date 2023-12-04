#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using integer = long long;

constexpr integer base = 31, modulus = 1000000007;

integer powers[101][2];

void initialize_hashing()
{
    powers[0][0] = 1;
    powers[0][1] = 1;

    for (size_t i = 1; i < 101; ++i) {
        powers[i][0] = powers[i-1][0] * base % modulus;

        powers[i][1] = 1;
        for (integer b = powers[i][0], p = modulus - 2; p != 0; p /= 2) {
            if (p % 2 == 1)
                powers[i][1] = powers[i][1] * b % modulus;

            b = b * b % modulus;
        }
    }
}

class HashedString {
public:
    HashedString(const std::string& s)
        : s_(s)
    {
        const size_t n = s_.length();

        h_.resize(1 + n);
        for (size_t i = 0; i < n; ++i)
            h_[i+1] = (h_[i] + (s_[i] - 'a' + 1) * powers[i][0]) % modulus;
    }

    size_t length() const
    {
        return s_.length();
    }

    std::string_view substring(size_t i, size_t k) const
    {
        return s_.substr(i, k);
    }

    integer subhash(size_t i, size_t k) const
    {
        return (h_[i+k] - h_[i] + modulus) % modulus * powers[i][1] % modulus;
    }

private:
    const std::string_view s_;

    std::vector<integer> h_;

}; // class HashedString

void solve(const std::vector<HashedString>& s, size_t k, std::vector<std::string_view>& t)
{
    const size_t n = s.size();

    std::vector<integer> hashes;
    for (size_t i = 0; i < n; ++i) {
        const size_t m = s[i].length();

        std::vector<integer> h;
        for (size_t j = 0; j + k <= m; ++j)
            h.push_back(s[i].subhash(j, k));

        std::sort(h.begin(), h.end());
        hashes.insert(hashes.end(), h.begin(), std::unique(h.begin(), h.end()));
    }

    std::sort(hashes.begin(), hashes.end());

    for (size_t i = 0; i < n; ++i) {
        if (k >= t[i].length())
            continue;

        for (size_t j = 0; j + k <= s[i].length(); ++j) {
            const integer h = s[i].subhash(j, k);

            const auto it = std::next(std::lower_bound(hashes.begin(), hashes.end(), h));
            if (it == hashes.end() || *it != h) {
                t[i] = s[i].substring(j, k);
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

    initialize_hashing();

    std::vector<HashedString> hs;
    hs.reserve(n);
    for (size_t i = 0; i < n; ++i)
        hs.emplace_back(s[i]);

    std::vector<std::string_view> t(n);
    for (size_t i = 0; i < n; ++i)
        t[i] = s[i];

    for (size_t k = 1; k <= 100; ++k)
        solve(hs, k, t);

    for (size_t i = 0; i < n; ++i)
        std::cout << t[i] << '\n';

    return 0;
}
