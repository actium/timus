#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

class SegmentTree {
public:
    explicit SegmentTree(size_t capacity)
        : capacity_(capacity)
        , data_(2 * capacity_)
        , consumption_(0)
    {}

    unsigned insert(unsigned value)
    {
        const size_t index = capacity_ + consumption_;
        index_.emplace(value, index);
        data_[index] = value;
        ++consumption_;
        return reduce(index);
    }

    unsigned remove(unsigned value)
    {
        const auto it = index_.find(value);
        const size_t index = it->second;
        index_.erase(it);
        data_[index] = 0;
        return reduce(index);
    }

private:
    unsigned reduce(size_t index)
    {
        while (index > 1) {
            const size_t parent = index >> 1;
            data_[parent] = std::gcd(data_[index], data_[index^1]);
            index = parent;
        }
        return data_[1] == 0 ? 1 : data_[1];
    }

private:
    const size_t capacity_;

    std::vector<unsigned> data_;
    size_t consumption_;

    std::unordered_multimap<unsigned, size_t> index_;

}; // class SegmentTree

int main()
{
    unsigned q;
    std::cin >> q;

    SegmentTree s(q);
    for (unsigned i = 0; i < q; ++i) {
        char t;
        std::cin >> t;

        unsigned x;
        std::cin >> x;

        std::cout << (t == '+' ? s.insert(x) : s.remove(x)) << '\n';
    }

    return 0;
}
