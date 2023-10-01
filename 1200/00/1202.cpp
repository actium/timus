#include <iostream>
#include <vector>

struct Rectangle {
    int x1;
    int y1;

    int x2;
    int y2;
};

int solve(const std::vector<Rectangle>& rs)
{
    const size_t n = rs.size();

    int x = 1, y = 1, d = 0;
    for (size_t i = 1; i < n; ++i) {
        if (rs[i].y1 + 1 >= rs[i-1].y2 || rs[i].y2 - 1 <= rs[i-1].y1)
            return -1;

        if (y <= rs[i].y1) {
            d += rs[i].y1 - y + 1;
            y = rs[i].y1 + 1;
        }
        if (y >= rs[i].y2 - 1) {
            d += y - rs[i].y2 + 1;
            y = rs[i].y2 - 1;
        }

        d += rs[i].x2 - x - 1;
        x = rs[i].x2 - 1;
    }

    d += rs[n-1].x2 - 1 - x;
    d += rs[n-1].y2 - 1 - y;

    return d;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<Rectangle> rs(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> rs[i].x1 >> rs[i].y1 >> rs[i].x2 >> rs[i].y2;

    std::cout << solve(rs) << '\n';

    return 0;
}
