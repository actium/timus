#include <iostream>
#include <vector>

constexpr unsigned modulus = 1000000000;

unsigned lsb(unsigned x)
{
    return x & -x;
}

class Tree {
public:
    explicit Tree(size_t size)
        : data_(1 + size)
    {}

    void increase(size_t index, unsigned delta)
    {
        const size_t n = data_.size();

        for (size_t i = 1 + index; i < n; i += lsb(i))
            data_[i] = (data_[i] + delta) % modulus;
    }

    unsigned sum(size_t upper_bound) const
    {
        unsigned s = 0;
        for (size_t i = 1 + upper_bound; i > 0; i &= ~lsb(i))
            s = (s + data_[i]) % modulus;

        return s;
    }

private:
    std::vector<unsigned> data_;

}; // class Tree

unsigned solve(const std::vector<unsigned>& a, size_t k)
{
    const size_t n = a.size();

    std::vector<Tree> t(k, Tree(1 + n));
    for (auto it = a.rbegin(); it != a.rend(); ++it) {
        t[0].increase(*it, 1);

        for (size_t j = 1; j < k; ++j)
            t[j].increase(*it, t[j-1].sum(*it - 1));
    }
    return t[k-1].sum(n);
}

int main()
{
    size_t n, k;
    std::cin >> n >> k;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::cout << solve(a, k) << '\n';

    return 0;
}
