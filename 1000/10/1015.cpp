#include <iostream>
#include <map>
#include <tuple>
#include <utility>
#include <vector>

struct Dice {
    unsigned left;
    unsigned right;
    unsigned top;
    unsigned front;
    unsigned bottom;
    unsigned back;

    void normalize()
    {
        if (left == 1 || right == 1)
            left = std::exchange(top, std::exchange(right, std::exchange(bottom, left)));

        while (front != 1)
            front = std::exchange(top, std::exchange(back, std::exchange(bottom, front)));

        for (const unsigned x = 2 + (back == 2); top != x; )
            left = std::exchange(top, std::exchange(right, std::exchange(bottom, left)));
    }

    bool operator <(const Dice& rhs) const
    {
        return std::make_tuple(left, right, top, front, bottom, back)
            < std::make_tuple(rhs.left, rhs.right, rhs.top, rhs.front, rhs.bottom, rhs.back);
    }

    bool operator ==(const Dice& rhs) const
    {
        return std::make_tuple(left, right, top, front, bottom, back)
            == std::make_tuple(rhs.left, rhs.right, rhs.top, rhs.front, rhs.bottom, rhs.back);
    }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Dice> d(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> d[i].left >> d[i].right >> d[i].top >> d[i].front >> d[i].bottom >> d[i].back;

    std::vector<std::vector<unsigned>> p;
    {
        std::map<Dice, size_t> x;
        for (size_t i = 0; i < n; ++i) {
            d[i].normalize();

            const auto s = x.emplace(d[i], p.size());
            if (s.second)
                p.emplace_back();

            p[s.first->second].push_back(1 + i);
        }
    }

    std::cout << p.size() << '\n';
    for (const std::vector<unsigned>& v : p) {
        for (const unsigned x : v)
            std::cout << x << ' ';

        std::cout << '\n';
    }

    return 0;
}
