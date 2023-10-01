#include <vector>

#include <cstdio>

constexpr unsigned size = 1 + 1000000;

class BinaryIndexedTree {
public:
    void adjust(unsigned index, int delta)
    {
        for (unsigned i = 1 + index; i <= size; i += i & -i)
            data_[i] += delta;
    }

    unsigned count(unsigned index) const
    {
        unsigned s = 0;

        unsigned r = size;
        while (r > index) {
            s += data_[r];
            r &= r - 1;
        }
        while (index > r) {
            s -= data_[index];
            index &= index - 1;
        }

        return s;
    }

private:
    unsigned data_[1 + size] = {};

}; // class BinaryIndexedTree

struct Operation {
    char type;
    unsigned price;
    unsigned count;

    Operation(char t, unsigned p, unsigned c)
        : type(t), price(p), count(c)
    {}
};

double solve(const std::vector<Operation>& ops)
{
    unsigned long long v = 0;

    BinaryIndexedTree t;
    for (const Operation& op : ops) {
        switch (op.type) {
            case 'B':
                t.adjust(op.price, +1);
                break;
            case 'D':
                t.adjust(op.price, -1);
                break;
            case 'S':
                v += std::min(t.count(op.price), op.count);
                break;
        }
    }

    return v / 100.0;
}

int main()
{
    std::vector<Operation> ops;
    while (true) {
        char s[5];
        scanf("%s", s);

        if (s[0] == 'Q')
            break;

        double x;
        scanf("%lf", &x);

        if (s[0] == 'S') {
            unsigned k;
            scanf("%u", &k);

            ops.emplace_back('S', x * 100 + 0.5, k);
        } else {
            ops.emplace_back(s[0], x * 100 + 0.5, 1);
        }
    }

    printf("%.02lf\n", solve(ops));

    return 0;
}
