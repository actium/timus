#include <iostream>

void answer(unsigned k, unsigned n, unsigned b, unsigned r, unsigned q)
{
    std::cout << "King: " << k << '\n';
    std::cout << "Knight: " << n << '\n';
    std::cout << "Bishop: " << b << '\n';
    std::cout << "Rook: " << r << '\n';
    std::cout << "Queen: " << q << '\n';
}

void solve(unsigned s, unsigned x, unsigned y)
{
    constexpr std::pair<int, int> d[8] = {
        { -2, 1 }, { -1, 2 }, { 1, 2 }, { 2, 1 }, { 2, -1 }, { 1, -2 }, { -1, -2 }, { -2, -1 }
    };

    const unsigned dx = std::min(x - 1, s - x);
    const unsigned dy = std::min(y - 1, s - y);

    unsigned k = 8;
    if (dx == 0)
        k -= 3;
    if (dy == 0)
        k -= 3;
    if (dx == 0 && dy == 0)
        k += 1;

    unsigned n = 0;
    for (const std::pair<int, int>& q : d) {
        if (x + q.first < 1 || x + q.first > s)
            continue;

        if (y + q.second < 1 || y + q.second > s)
            continue;

        ++n;
    }

    const unsigned b = s - 1 + 2 * std::min(dx, dy);
    const unsigned r = 2 * (s - 1);
    const unsigned q = b + r;

    answer(k, n, b, r, q);
}

int main()
{
    unsigned n;
    std::cin >> n;

    unsigned x, y;
    std::cin >> x >> y;

    switch (n) {
        case 1:
            answer(0, 0, 0, 0, 0);
            break;
        case 2:
            answer(3, 0, 1, 2, 3);
            break;
        default:
            solve(n, x, y);
            break;
    }

    return 0;
}
