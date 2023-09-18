#include <iostream>

std::pair<int, int> convert(unsigned x)
{
    unsigned d = 0, s = 1, r = 1;
    while (s < x) {
        ++d;
        s += 2 * d + 1;
        r += 2;
    }

    return std::make_pair(r - (s - x) % 2, (x + 2 * d - s) / 2);
}

int main()
{
    unsigned n, m;
    std::cin >> n >> m;

    const auto p1 = convert(n), p2 = convert(m);

    const unsigned di = abs(p2.first - p1.first), dj = abs(p2.second - p1.second);
    std::cout << di + 2 * (dj - std::min(di / 2, dj)) << '\n';

    return 0;
}
