#include <iostream>

#include <cassert>

struct Position {
    unsigned r;
    unsigned c;
};

std::istream& operator >>(std::istream& input_stream, Position& position)
{
    return input_stream >> position.r >> position.c;
}

const char* solve(unsigned n, Position b, Position r)
{
    if (b.c > r.c) {
        b.c = 1 + n - b.c;
        r.c = 1 + n - r.c;
    }

    if (b.r == r.r) {
        assert(r.c > b.c);

        const auto d = (r.c - b.c - 1) / 2;
        b.c += d;
        r.c -= d;
        if (r.c - b.c == 2)
            ++b.c;

        assert(r.c - b.c == 1);
        return b.c - 1 > n - r.c ? "Blue" : "Red";
    }

    if (r.c - b.c == 0)
        return "Red";

    if (r.c - b.c == 1)
        return b.c - 1 != n - r.c ? "Blue" : "Red";

    if (r.c - b.c >= 4) {
        const auto d = (r.c - b.c - 2) / 2;
        b.c += d;
        r.c -= d;
    }

    if (r.c - b.c == 2)
        return b.c - 1 > n - r.c + 1 ? "Blue" : "Red";

    assert(r.c - b.c == 3);
    return b.c + (n % 2) > n - r.c + (1 - n % 2) ? "Blue" : "Red";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    Position b, r;
    std::cin >> b >> r;

    std::cout << solve(n, b, r) << '\n';

    return 0;
}
