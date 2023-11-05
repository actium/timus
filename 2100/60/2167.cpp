#include <array>
#include <iostream>
#include <vector>

class BitTrie {
public:
    BitTrie()
        : nodes_(1)
    {}

    void insert(unsigned x)
    {
        for (size_t i = 20, node = 0; i-- > 0; ) {
            const unsigned bit = (x >> i) & 1;
            if (nodes_[node][bit] == 0) {
                nodes_[node][bit] = nodes_.size();
                nodes_.emplace_back();
            }
            node = nodes_[node][bit];
        }
    }

    unsigned search(unsigned x) const
    {
        unsigned v = 0;
        for (size_t i = 20, node = 0; i-- > 0; ) {
            const unsigned bit = (x >> i) & 1;
            if (nodes_[node][bit] != 0) {
                node = nodes_[node][bit];
            } else {
                v |= 1 << i;
                node = nodes_[node][bit^1];
            }
        }
        return v;
    }

private:
    std::vector<std::array<unsigned, 2>> nodes_;

}; // class BitTrie

BitTrie prepare()
{
    constexpr unsigned ub = 1 << 20;

    BitTrie bt;
    {
        unsigned x = 3;
        if (x <= ub)
            bt.insert(2);

        std::vector<bool> c(ub);
        for (unsigned i = 9; i < ub; i += 4 * ++x, ++x) {
            if (c[x])
                continue;

            bt.insert(x);

            for (unsigned j = i; j < ub; j += 2 * x)
                c[j] = true;
        }
        for ( ; x < ub; x += 2) {
            if (!c[x])
                bt.insert(x);
        }
    }
    return bt;
}

void solve(const std::vector<unsigned>& a)
{
    const BitTrie bt = prepare();
    for (const unsigned x : a)
        std::cout << bt.search(x) << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t t;
    std::cin >> t;

    std::vector<unsigned> a(t);
    for (size_t i = 0; i < t; ++i)
        std::cin >> a[i];

    solve(a);

    return 0;
}
