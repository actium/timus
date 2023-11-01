#include <iostream>
#include <string>
#include <vector>

class SparseTable {
public:
    explicit SparseTable(const std::vector<unsigned>& data)
    {
        const size_t n = data.size();

        unsigned h = 1;
        while ((1 << h) <= n)
            ++h;

        data_.resize(h, std::vector<unsigned>(n));
        for (size_t j = 0; j < n; ++j)
            data_[0][j] = data[j];

        for (size_t i = 1; i < h; ++i) {
            for (size_t j = 0; j < n; ++j)
                data_[i][j] = std::min(data_[i-1][j], data_[i-1][std::min(j + (1 << i - 1), n - 1)]);
        }
    }

    unsigned query(unsigned l, unsigned r) const
    {
        const unsigned x = __builtin_clz(1) - __builtin_clz(r - l);
        return std::min(data_[x][l], data_[x][r - (1 << x)]);
    }

private:
    std::vector<std::vector<unsigned>> data_;

}; // class SparseTable

std::string solve(const std::string& s, const std::vector<std::pair<unsigned, unsigned>>& r)
{
    const size_t n = s.length(), q = r.size();

    std::vector<unsigned> h(n + 1);
    {
        std::vector<size_t> b;
        for (size_t i = 0; i < n; ++i) {
            if (isupper(s[i])) {
                b.push_back(i);
                continue;
            }

            if (b.empty())
                continue;

            if (s[b.back()] == toupper(s[i])) {
                ++h[b.back()];
                --h[i+1];
                b.pop_back();
            } else {
                b.clear();
            }
        }
    }

    for (size_t i = 1; i <= n; ++i)
        h[i] += h[i-1];

    const SparseTable t(h);

    std::string v(q, '0');
    for (size_t i = 0; i < q; ++i) {
        if ((r[i].second - r[i].first) % 2 == 0 || h[r[i].first] == 0 || h[r[i].second] != h[r[i].first])
            continue;

        if (islower(s[r[i].first]) || isupper(s[r[i].second]))
            continue;

        if (t.query(r[i].first, r[i].second) == h[r[i].first])
            ++v[i];
    }
    return v;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    size_t q;
    std::cin >> q;

    std::vector<std::pair<unsigned, unsigned>> r(q);
    for (size_t i = 0; i < q; ++i) {
        std::cin >> r[i].first >> r[i].second;

        --r[i].first;
        --r[i].second;
    }

    std::cout << solve(s, r) << '\n';

    return 0;
}
