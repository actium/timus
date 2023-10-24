#include <iostream>
#include <utility>
#include <vector>

class DisjointSetUnion {
public:
    explicit DisjointSetUnion(unsigned size)
        : roots_(size)
        , ranks_(size)
    {
        for (size_t i = 0; i < size; ++i)
            roots_[i] = i;
    }

    bool merge(unsigned u, unsigned v)
    {
        unsigned ru = resolve(u), rv = resolve(v);
        if (ru == rv)
            return false;

        if (ranks_[ru] < ranks_[rv])
            std::swap(ru, rv);

        roots_[rv] = ru;

        if (ranks_[ru] == ranks_[rv])
            ++ranks_[ru];

        return true;
    }

private:
    unsigned resolve(unsigned id)
    {
        while (id != roots_[id])
            id = std::exchange(roots_[id], roots_[roots_[id]]);

        return id;
    }

private:
    std::vector<unsigned> roots_;
    std::vector<unsigned> ranks_;

}; // class DisjointSetUnion

void solve(unsigned k)
{
    using integer = unsigned long long;

    std::vector<std::vector<unsigned>> r(k);
    for (integer i = 1; i < 2 * k + 2; ++i)
        r[i * i % k].push_back(i);

    DisjointSetUnion dsu(2 * k + 10);
    for (integer a = 1; ; ++a) {
        const unsigned x = (k - a * a % k) % k;
        if (x != 0 && x < a && !dsu.merge(a, x)) {
            std::cout << a << '\n';
            return;
        }

        for (const unsigned b : r[(k - a % k) % k]) {
            if (b >= a)
                break;

            if (b != x && !dsu.merge(a, b)) {
                std::cout << a << '\n';
                return;
            }
        }
    }
}

int main()
{
    unsigned k;
    std::cin >> k;

    solve(k);

    return 0;
}
