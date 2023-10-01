#include <iostream>
#include <string>

std::string solve(std::string& s, const std::string& t)
{
    const size_t n = s.length(), m = t.length();

    size_t p = 0;

    const auto next = [&] {
        while (p < m && t[p] == ' ')
            ++p;

        std::string s;
        while (p < m && t[p] != ' ')
            s.push_back(t[p++]);

        return s;
    };

    size_t x = 0;

    const auto drop = [&](size_t d, size_t k) {
        while (x < d) {
            if (s[x] != ' ')
                s[x] = '_';

            ++x;
        }

        x += k;

        if (x < n && s[x] != ' ')
            s[x] = '_';

        ++x;
    };

    for (std::string q = next(); !q.empty(); q = next()) {
        const size_t d = s.find(q, x);
        if (d == std::string::npos)
            return "I HAVE FAILED!!!";

        drop(d, q.length());
    }

    drop(n, 0);

    return s;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s;
    std::getline(std::cin, s);

    std::string t;
    std::getline(std::cin, t);

    std::cout << solve(s, t) << '\n';

    return 0;
}
