#include <algorithm>
#include <iostream>
#include <string>

const std::string t[] = {
    "Alice",    "Ariel",    "Aurora",
    "Bambi",    "Belle",    "Bolt",
    "Dumbo",    "Genie",    "Jiminy",

    "Phil",     "Peter",    "Olaf",
    "Mulan",    "Mowgli",   "Mickey",
    "Kuzko",    "Kida",     "Kenai",

    "Phoebus",  "Ralph",    "Robin",
    "Silver",   "Simba",    "Stitch",
    "Tarzan",   "Tiana",    "Winnie",
};

int main()
{
    size_t n;
    std::cin >> n;

    unsigned x = 0, d = 0;
    for (size_t i = 0; i < n; ++i) {
        std::string a;
        std::cin >> a;

        const auto it = std::find(std::cbegin(t), std::cend(t), a);

        const int dx = std::distance(std::cbegin(t), it) % 9 / 3 - x;
        d += std::abs(dx);
        x += dx;
    }

    std::cout << d << '\n';

    return 0;
}
