#include <iostream>
#include <vector>

inline unsigned lsb(unsigned x)
{
    return x & -x;
}

class BIT {
public:
    explicit BIT(size_t size)
        : data_(1 + size)
    {}

    void increment(unsigned index)
    {
        const unsigned n = data_.size();
        for (unsigned i = index + 1; i < n; i += lsb(i))
            ++data_[i];
    }

    unsigned sum(unsigned right) const
    {
        unsigned s = 0;
        for (unsigned i = right + 1; i > 0; i &= i - 1)
            s += data_[i];

        return s;
    }

private:
    std::vector<unsigned> data_;

}; // class BIT

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, k;
    std::cin >> n >> k;

    std::vector<unsigned> q(k);
    for (size_t i = 0; i < k; ++i) {
        BIT bit(n);
        for (size_t j = 0; j < n; ++j) {
            unsigned x;
            std::cin >> x;
            q[i] += bit.sum(n - x);
            bit.increment(n - x);
        }
    }

    size_t x = 0;
    for (size_t i = 1; i < k; ++i) {
        if (q[i] > q[x])
            x = i;
    }

    std::cout << 1 + x << '\n';

    return 0;
}
