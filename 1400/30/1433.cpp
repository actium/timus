#include <iostream>
#include <string>

constexpr size_t p[][4] = {
    {0, 1, 2, 3},
    {0, 3, 1, 2},
    {0, 2, 3, 1},

    {1, 3, 2, 0},
    {1, 0, 3, 2},
    {1, 2, 0, 3},

    {2, 1, 3, 0},
    {2, 0, 1, 3},
    {2, 3, 0, 1},

    {3, 2, 1, 0},
    {3, 0, 2, 1},
    {3, 1, 0, 2},
};

const char* solve(const std::string& s, const std::string& t)
{
    const auto check = [&](const size_t x[4]) {
        for (size_t i = 0; i < 4; ++i) {
            if (s[x[i]] != t[i])
                return false;
        }
        return true;
    };

    for (const auto& q : p) {
        if (check(q))
            return "equal";
    }
    return "different";
}

int main()
{
    std::string s, t;
    std::cin >> s >> t;

    std::cout << solve(s, t) << '\n';;

    return 0;
}
