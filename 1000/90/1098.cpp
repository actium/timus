#include <iostream>
#include <string>
#include <vector>

constexpr unsigned N = 1999;

class BinaryIndexedTree {
public:
    explicit BinaryIndexedTree(unsigned size)
        : data_(1 + size, 1)
    {
        for (unsigned i = 1; i <= size; ++i) {
            const unsigned j = i + (i & -i);
            if (j <= size)
                data_[j] += data_[i];
        }
    }

    void reset(unsigned index)
    {
        const unsigned n = data_.size();
        for (unsigned i = 1 + index; i < n; i += i & -i)
            --data_[i];
    }

    unsigned lower_bound(unsigned target_sum) const
    {
        const unsigned n = data_.size();

        unsigned p = 0;
        for (unsigned i = 1 << __builtin_clz(1) - __builtin_clz(n); i != 0; i >>= 1) {
            if (p + i < n && data_[p+i] < target_sum) {
                target_sum -= data_[p + i];
                p += i;
            }
        }
        return p;
    }

private:
    std::vector<unsigned> data_;

}; // class BinaryIndexedTree

const char* solve(std::string& t)
{
    size_t n = t.length();

    BinaryIndexedTree bit(n);
    for (unsigned x = 0; n > 1; --n, x %= n) {
        x = (x + N - 1) % n;
        bit.reset(bit.lower_bound(x + 1));
    }

    const char c = t[bit.lower_bound(1)];
    if (c == '?')
        return "Yes";
    if (c == ' ')
        return "No";

    return "No comments";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string t;
    for (std::string s; std::getline(std::cin, s); t.append(s));

    std::cout << solve(t) << '\n';

    return 0;
}
