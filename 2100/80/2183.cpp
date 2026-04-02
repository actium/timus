#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

constexpr int oo = 1000000000;

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

int solve(const std::vector<int>& a)
{
    const size_t n = a.size();

    const RangeQueryTable<int> t_min(a.begin(), a.end(), [](int x, int y) { return std::min(x, y); });
    const RangeQueryTable<int> t_max(a.begin(), a.end(), [](int x, int y) { return std::max(x, y); });

    std::vector<size_t> p(n);
    for (size_t i = 0; i < n; ++i)
        p[i] = i;

    std::sort(p.begin(), p.end(), [&](size_t i, size_t j) { return a[i] < a[j]; });

    int v = -oo;
    {
        std::pair<size_t, size_t> r = { p[0], p[0]+1 };
        for (size_t i = 0; i < n; ++i) {
            r.first = std::min(r.first, p[i]);
            r.second = std::max(r.second, p[i]+1);

            const int pv = (r.first == 0 ? oo : t_min.query<false>(0, r.first));
            const int cv = -t_max.query<false>(r.first, r.second);
            const int sv = (r.second == n ? oo : t_min.query<false>(r.second, n));

            v = std::max(v, std::min({ pv, cv, sv }));
        }
    }
    return v;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<int> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::cout << solve(a) << '\n';

    return 0;
}
