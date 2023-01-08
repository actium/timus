#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
std::istream& operator >>(std::istream& input, std::vector<T>& v)
{
    for (T& a : v)
        input >> a;

    return input;
}

class Hash {
    static constexpr size_t N = 100000;
    static constexpr unsigned P = 1000000123;
    static constexpr unsigned M = (1u << 31) - 1;

    static std::vector<unsigned> powers_;

public:
    explicit Hash(const std::vector<char>& s)
    {
        const size_t n = s.size();

        powers_.reserve(1 + n);
        while (powers_.size() <= n)
            powers_.push_back(1ull * powers_.back() * P % M);

        data_.resize(1 + n);
        for (size_t i = 0; i < n; ++i)
            data_[1 + i] = (data_[i] + 1ull * s[i] * powers_[i]) % M;
    }

    unsigned select(size_t i, size_t k) const
    {
        const uint64_t h = (M + data_[i + k] - data_[i]) % M;
        return h * powers_[data_.size() - i - k] % M;
    }

private:
    std::vector<unsigned> data_;

}; // class Hasher

std::vector<unsigned> Hash::powers_ = { 1 };

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<char> s(n), t(n);
    std::cin >> s >> t;

    const Hash hs(s), ht(t);

    const auto check = [&](size_t k) {
        std::vector<std::pair<unsigned, size_t>> c(n - k + 1);
        for (size_t i = 0; i + k <= n; ++i)
            c[i] = std::make_pair(ht.select(i, k), i);

        std::sort(c.begin(), c.end());

        for (size_t i = 0; i + k <= n; ++i) {
            const unsigned h = hs.select(i, k);

            const auto it = std::lower_bound(c.begin(), c.end(), h, [&](const auto& x, unsigned v) {
                return x.first < v;
            });
            if (it != c.end() && it->first == h && std::equal(s.begin() + i, s.begin() + i + k, t.begin() + it->second))
                return i;
        }
        return n;
    };

    size_t x = n, lb = 0, ub = n + 1;
    while (lb + 1 < ub) {
        const size_t mid = (lb + ub) / 2;

        const size_t p = check(mid);
        if (p < n) {
            x = p;
            lb = mid;
        } else {
            ub = mid;
        }
    }

    for (size_t i = 0; i < lb; ++i)
        std::cout << s[x + i];

    return 0;
}
