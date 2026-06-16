#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

template <typename T, typename F = std::function<T(T, T)>>
class RangeQueryTable {
public:
    template <typename Iterator>
    RangeQueryTable(Iterator begin, Iterator end, F&& combine)
        : combine_(std::forward<F>(combine))
    {
        const unsigned n = end - begin;

        data_.reserve(w - __builtin_clz(n) + 1);
        data_.emplace_back(begin, end);
        for (unsigned i = 1; (1 << i) <= n; ++i) {
            const unsigned k = n - (1 << i) + 1;

            data_.emplace_back(k);
            for (unsigned j = 0; j < k; ++j)
                data_[i][j] = combine_(data_[i-1][j], data_[i-1][j+(1 << i-1)]);
        }
    }

    template <bool cascading>
    T query(unsigned range_begin, unsigned range_end) const
    {
        unsigned x = w - __builtin_clz(range_end - range_begin);

        T value = data_[x][range_begin];
        if constexpr (!cascading) {
            value = combine_(value, data_[x][range_end - (1 << x)]);
        } else {
            for (range_begin += 1 << x; range_begin < range_end; range_begin += 1 << x) {
                x = w - __builtin_clz(range_end - range_begin);
                value = combine_(value, data_[x][range_begin]);
            }
        }
        return value;
    }

private:
    const F combine_;

    std::vector<std::vector<T>> data_;

    static constexpr unsigned w = __builtin_clz(1);

}; // class RangeQueryTable<T, F>

unsigned solve(const std::vector<unsigned>& s)
{
    const size_t k = s.size();

    std::vector<size_t> p(k+1);

    const auto prepare = [&](size_t b) {
        std::map<std::pair<unsigned, unsigned>, size_t> x;
        for ( ; b + 1 < k; b += 2) {
            const auto e = std::minmax(s[b], s[b+1]);

            if (e.first == 0 || e.first == e.second) {
                for (const auto& e : x)
                    p[e.second] = b;

                x.clear();

                p[b] = b;
                continue;
            }

            if (auto it = x.find(e); it != x.end()) {
                for (size_t j = it->second; j >= 2; j -= 2) {
                    const auto jt = x.find(std::minmax(s[j], s[j+1]));
                    if (jt == x.end() || jt->second > j)
                        break;

                    p[jt->second] = b;
                    x.erase(jt);
                }
            }

            x.emplace(e, b);
        }

        for (const auto& e : x)
            p[e.second] = b;
    };

    prepare(2);
    prepare(3);

    p[k-1] = k-1;
    p[k-0] = k-0;

    const RangeQueryTable<unsigned> rqt(s.begin(), s.end(), [](unsigned x, unsigned y) { return std::max(x, y); });

    unsigned q = 0;
    for (size_t i = 2; i <= k; ++i) {
        const unsigned n = s[i-2];
        if (n == 0)
            continue;

        const unsigned m = s[i-1];
        if (i + 2 * m > p[i])
            continue;

        if (m == 0 || rqt.query<false>(i, i + 2 * m) <= n)
            ++q;
    }
    return q;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t k;
    std::cin >> k;

    std::vector<unsigned> s(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> s[i];

    std::cout << solve(s) << '\n';

    return 0;
}
