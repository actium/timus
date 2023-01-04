#include <algorithm>
#include <iostream>
#include <vector>

inline size_t lsb(size_t x)
{
    return x & -x;
}

class BinaryIndexedTree {
public:
    explicit BinaryIndexedTree(size_t size)
        : data_(1 + size)
    {}

    void adjust(size_t index, int delta)
    {
        const size_t n = data_.size();
        for (size_t i = 1 + index; i < n; i += lsb(i))
            data_[i] += delta;
    }

    long long sum(size_t right) const
    {
        long long s = 0;
        for (size_t i = 1 + right; i > 0; i &= ~lsb(i))
            s += data_[i];

        return s;
    }

private:
    std::vector<long long> data_;

}; // class BinaryIndexedTree

std::vector<std::vector<unsigned>> fs;

const std::vector<unsigned>& factors(unsigned x)
{
    std::vector<unsigned>& v = fs[x-1];
    if (v.empty()) {
        for (unsigned i = 1; i * i <= x; ++i) {
            if (x % i == 0) {
                v.push_back(i);
                v.push_back(x / i);
            }
        }
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
    }
    return v;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    fs.resize(n);

    BinaryIndexedTree da(1 + n + 1);

    const auto update = [&](unsigned l, unsigned r, int d) {
        da.adjust(l, d);
        da.adjust(r + 1, -d);
    };

    const auto query = [&](unsigned x) {
        long long s = a[x-1];
        for (const unsigned f : factors(x))
            s += da.sum(f);

        return s;
    };

    unsigned q;
    std::cin >> q;

    while (q-- != 0) {
        unsigned t;
        std::cin >> t;

        if (t == 1) {
            unsigned i;
            std::cin >> i;

            std::cout << query(i) << '\n';
        } else {
            unsigned l, r, d;
            std::cin >> l >> r >> d;

            update(l, r, d);
        }
    }

    return 0;
}
