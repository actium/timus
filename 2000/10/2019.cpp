#include <iostream>
#include <string>
#include <vector>

bool solve(const std::string& s, std::vector<unsigned>& t)
{
    unsigned x[2] = { 1, 1 };

    std::vector<std::pair<char, unsigned>> q;
    for (const char c : s) {
        if (isupper(c)) {
            if (q.empty() || isupper(q.back().first) || toupper(q.back().first) != c) {
                q.emplace_back(c, x[0]);
            } else {
                t[x[0]-1] = q.back().second;
                q.pop_back();
            }
            ++x[0];
        } else {
            if (q.empty() || islower(q.back().first) || tolower(q.back().first) != c) {
                q.emplace_back(c, x[1]);
            } else {
                t[q.back().second-1] = x[1];
                q.pop_back();
            }
            ++x[1];
        }
    }
    return q.empty();
}

int main()
{
    size_t n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    std::vector<unsigned> t(n);
    if (!solve(s, t)) {
        std::cout << "Impossible" << '\n';
    } else {
        for (const unsigned x : t)
            std::cout << x << ' ';
    }

    return 0;
}
