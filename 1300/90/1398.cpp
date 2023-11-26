#include <iostream>
#include <string>

const char* solve(const std::string& b, const std::string& p)
{
    if (p == "a3" && b == "b1" || p == "h3" && b == "g1")
        return "DRAW";

    if (p == "b2" && b == "a2" || p == "g2" && b == "h2")
        return "DRAW";

    if (p.back() >= '3')
        return "WHITE";

    if ((p.front() - b.front() + b.back() - '1') % 2 == 0)
        return "WHITE";

    if (b.back() == '1' && abs(b.front() - p.front()) == 1)
        return "WHITE";

    for (char x = p.front() - 1; x >= 'a'; --x) {
        if (b.front() == x && b.back() - (p.front() - x) == p.back())
            return "WHITE";
    }
    for (char x = p.front() + 1; x <= 'h'; ++x) {
        if (b.front() == x && b.back() - (x - p.front()) == p.back())
            return "WHITE";
    }

    return "BLACK";
}

int main()
{
    std::string b, p;
    std::cin >> b >> p;

    std::cout << solve(b, p) << '\n';

    return 0;
}
