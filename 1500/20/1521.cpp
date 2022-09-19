#include <iostream>
#include <vector>

uint32_t lsb(uint32_t x)
{
    return x & -x;
}

class Tree {
public:
    explicit Tree(size_t size)
        : data_(1 + size, 1)
    {
        for (size_t i = 1; i <= size; ++i) {
            const size_t j = i + lsb(i);
            if (j <= size)
                data_[j] += data_[i];
        }
    }

    void reset(size_t index)
    {
        const size_t n = data_.size();

        for (size_t i = 1 + index; i < n; i += lsb(i))
            --data_[i];
    }

    std::pair<unsigned, unsigned> get_sums(size_t x) const
    {
        const unsigned p = sum(x), s = sum(data_.size()-1);
        return std::make_pair(p, s - p);
    }

    size_t search(unsigned target) const
    {
        const size_t n = data_.size();

        size_t p = 0;
        for (size_t i = 1 << 31 - __builtin_clz(n); i != 0; i >>= 1) {
            if (p + i < n && data_[p + i] < target) {
                target -= data_[p + i];
                p += i;
            }
        }
        return p;
    }

private:
    unsigned sum(size_t i) const
    {
        unsigned s = 0;
        while (i > 0) {
            s += data_[i];
            i &= ~lsb(i);
        }
        return s;
    }

private:
    std::vector<unsigned> data_;

}; // class Tree

int main()
{
    unsigned n, k;
    std::cin >> n >> k;

    Tree t(n);
    for (size_t i = 0, x = 0; i < n; ++i, t.reset(x)) {
        const std::pair<unsigned, unsigned> s = t.get_sums(x);

        const unsigned g = (s.second >= k ? s.first + k : k - s.second);
        x = t.search(1 + (g - 1) % (n - i));
        std::cout << 1 + x << ' ';
    }

    return 0;
}
