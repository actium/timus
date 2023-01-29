#include <iostream>

struct Date {
    unsigned year;
    unsigned month;
    unsigned day;

    Date(unsigned d, unsigned m, unsigned y)
        : year(y), month(m), day(d)
    {}

    explicit Date(unsigned code)
    {
        unsigned x = code + 68569;

        const unsigned a = 4 * x / 146097;
        x -= (146097 * a + 3) / 4;

        const unsigned b = (4000 * (x + 1)) / 1461001;
        x -= 1461 * b / 4 - 31;

        const unsigned c = 80 * x / 2447;
        day = x - 2447 * c / 80;
        x = c / 11;
        month = c + 2 - 12 * x;
        year = 100 * (a - 49) + b + x;
    }

    unsigned hash() const
    {
        const int a = int(month - 14) / 12;
        const unsigned b = year + 4800 + a;
        return 1461 * b / 4 + 367 * (month - 2 - a * 12) / 12 - (b + 100) / 100 * 3 / 4 + day - 32075;
    }
};

int main()
{
    unsigned d, m, y;
    std::cin >> d >> m >> y;

    std::string c[7] = { "mon", "tue", "wed", "thu", "fri", "sat", "sun" };
    for (size_t i = 0, j = Date(1, m, y).hash() % 7; i < j; ++i)
        c[i] += "     ";

    for (unsigned i = 1; i <= 31; ++i) {
        const unsigned x = Date(i, m, y).hash();
        if (Date(x).month != m)
            break;

        std::string& r = c[x % 7];
        r.push_back(' ');
        r.push_back(i == d ? '[' : ' ');
        r.push_back(i < 10 ? ' ' : '0' + i / 10);
        r.push_back('0' + i % 10);
        r.push_back(i == d ? ']' : ' ');
    }

    for (size_t i = 0; i < 7; ++i)
        std::cout << c[i] << '\n';

    return 0;
}
