#include <iostream>

class Date {
public:
    operator unsigned() const
    {
        const int a = (m - 14) / 12;
        const int b = y + 4800 + a;
        return 1461 * b / 4 + 367 * (m - 2 - a * 12) / 12 - (b + 100) / 100 * 3 / 4 + d - 32075;
    }

private:
    int y;
    int m;
    int d;

    friend std::istream& operator >>(std::istream& input, Date& date)
    {
        char c;
        return input >> date.d >> c >> date.m >> c >> date.y;
    }

}; // class Date

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::pair<size_t, unsigned> x = {};
    for (size_t i = 0; i < n; ++i) {
        Date date[3];
        for (size_t j = 0; j < 3; ++j)
            std::cin >> date[j];

        const unsigned d = date[2] - date[0];
        if (d > x.second)
            x = { i, d };
    }

    std::cout << 1 + x.first << '\n';

    return 0;
}
