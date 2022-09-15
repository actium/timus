#include <iostream>
#include <string>

const char* solve(const std::string& s)
{
    unsigned f[2] = {};

    std::string t;
    for (const char c : s) {
        if (isalpha(c)) {
            t.push_back(c);
        } else {
            f[0] += (t == "tram");
            f[1] += (t == "trolleybus");

            t.clear();
        }
    }

    constexpr const char* r[3] = {
        "Tram driver",
        "Trolleybus driver",
        "Bus driver",
    };
    return r[(f[1] >= f[0]) + (f[1] == f[0])];
}

int main()
{
    std::string s;
    for (std::string b; std::getline(std::cin, b); s += b + " ");

    std::cout << solve(s) << '\n';

    return 0;
}
