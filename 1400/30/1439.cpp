#include <iostream>
#include <set>
#include <vector>

class Map {
public:
    explicit Map(unsigned n)
        : bucket_count_((n + 799) / 800)
    {
        buckets_.resize(bucket_count_);

        counts_.resize(1 + bucket_count_, 800);
        counts_[0] = 0;
        for (unsigned i = 1; i <= bucket_count_; ++i) {
            const unsigned j = i + (i & -i);
            if (j <= bucket_count_)
                counts_[j] += counts_[i];
        }
    }

    unsigned resolve(unsigned x) const
    {
        const unsigned p = lookup(x);

        if (p != 0)
            x -= sum(p - 1);

        unsigned d = 0;
        for (const unsigned q : buckets_[p]) {
            if (q > x + d)
                break;

            ++d;
        }

        return 800 * p + x + d;
    }

    void remove(unsigned x)
    {
        const unsigned p = lookup(x);

        if (p != 0)
            x -= sum(p - 1);

        unsigned d = 0;
        for (const unsigned q : buckets_[p]) {
            if (q > x + d)
                break;

            ++d;
        }

        buckets_[p].insert(x + d);

        for (unsigned i = 1 + p; i <= bucket_count_; i += i & -i)
            --counts_[i];
    }

private:
    unsigned lookup(unsigned target_sum) const
    {
        const unsigned n = counts_.size();

        unsigned p = 0;
        for (unsigned i = 1 << __builtin_clz(1) - __builtin_clz(n); i != 0; i >>= 1) {
            if (p + i < n && counts_[p + i] < target_sum) {
                target_sum -= counts_[p + i];
                p += i;
            }
        }
        return p;
    }

    unsigned sum(size_t right_index) const
    {
        unsigned s = 0;
        for (size_t i = right_index + 1; i > 0; i &= i - 1)
            s += counts_[i];

        return s;
    }

private:
    unsigned bucket_count_;

    std::vector<std::set<unsigned>> buckets_;
    std::vector<unsigned> counts_;

}; // class Map

void solve(unsigned n, const std::vector<std::pair<char, unsigned>>& q)
{
    Map v(n);
    for (const std::pair<char, unsigned>& r : q) {
        if (r.first == 'L') {
            std::cout << v.resolve(r.second) << '\n';
        } else {
            v.remove(r.second);
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    size_t m;
    std::cin >> m;

    std::vector<std::pair<char, unsigned>> q(m);
    for (size_t i = 0; i < m; ++i)
        std::cin >> q[i].first >> q[i].second;

    solve(n, q);

    return 0;
}
