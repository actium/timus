#include <iostream>
#include <vector>

using integer = long long;

inline unsigned lsb(unsigned x)
{
    return x & -x;
}

class Space {
public:
    explicit Space(size_t size)
        : size_(size)
        , data_(1 + size, std::vector<std::vector<int>>(1 + size, std::vector<int>(1 + size)))
    {}

    void update(int x, int y, int z, int delta)
    {
        for (int i = 1 + x; i <= size_; i += lsb(i)) {
            for (int j = 1 +  y; j <= size_; j += lsb(j)) {
                for (int k = 1 + z; k <= size_; k += lsb(k))
                    data_[i][j][k] += delta;
            }
        }
    }

    integer count(int x, int y, int z) const
    {
        integer sum = 0;
        for (int i = 1 + x; i > 0; i &= ~lsb(i)) {
            for (int j = 1 + y; j > 0; j &= ~lsb(j)) {
                for (int k = 1 + z; k > 0; k &= ~lsb(k))
                    sum += data_[i][j][k];
            }
        }
        return sum;
    }

    integer count(int x1, int y1, int z1, int x2, int y2, int z2) const
    {
        integer sum = 0;
        sum += count(x2, y2, z2);
        sum -= count(x1 - 1, y2, z2);
        sum -= count(x2, y1 - 1, z2);
        sum -= count(x2, y2, z1 - 1);
        sum += count(x1 - 1, y1 - 1, z2);
        sum += count(x1 - 1, y2, z1 - 1);
        sum += count(x2, y1 - 1, z1 - 1);
        sum -= count(x1 - 1, y1 - 1, z1 - 1);
        return sum;
    }

private:
    const size_t size_;

    std::vector<std::vector<std::vector<int>>> data_;

}; // class Space

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    Space s(n);
    while (true) {
        unsigned m;
        std::cin >> m;

        if (m == 1) {
            int x, y, z, d;
            std::cin >> x >> y >> z >> d;

            s.update(x, y, z, d);
            continue;
        }
        if (m == 2) {
            int x1, y1, z1, x2, y2, z2;
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

            std::cout << s.count(x1, y1, z1, x2, y2, z2) << '\n';
            continue;
        }
        break;
    }

    return 0;
}
