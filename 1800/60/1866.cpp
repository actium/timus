#include <iostream>
#include <string>
#include <vector>

const char* solve(const std::vector<std::string>& s)
{
    const size_t n = s.size();

    std::vector<std::string> t(n, "0");
    for (size_t i = 0; i < n; ++i) {
        for (size_t x = 0; x < s[i].length(); ++x) {
            if (s[i][x] == '[')
                ++t[i].back();

            if (s[i][x] == ' ' || s[i][x] == '-')
                t[i].push_back('0');
        }
    }

    const auto check = [&](std::string p) {
        for (size_t i = 0; i < n; ++i) {
            while (p.length() < t[i].length())
                p += p;

            if (p.compare(0, t[i].length(), t[i]) != 0)
                return false;
        }
        return true;
    };

    const std::string r = t[0].substr(0, 4);

    if (r == "1010" && check("10"))
        return "trochee";

    if (r == "0101" && check("01"))
        return "iamb";

    if (r == "1001" && check("100"))
        return "dactyl";

    if (r == "0100" && check("010"))
        return "amphibrach";

    if (r == "0010" && check("001"))
        return "anapaest";

    return "not a poem";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n >> std::ws;

    std::vector<std::string> s(n);
    for (size_t i = 0; i < n; ++i)
        std::getline(std::cin, s[i]);

    std::cout << solve(s) << '\n';

    return 0;
}
