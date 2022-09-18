#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Person {
    unsigned i;
    std::string s;
    unsigned t;

    Person(unsigned i, const std::string& s, const std::string& x)
        : i(i)
        , s(s)
    {
        t = (x[0] - '0') * 6000
          + (x[1] - '0') * 600
          + (x[3] - '0') * 100
          + (x[4] - '0') * 10
          + (x[6] - '0') * 1;
    }
};

bool operator <(const Person& lhs, const Person& rhs)
{
    return lhs.t + lhs.i * 300 < rhs.t + rhs.i * 300;
}

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<Person> w;
    for (size_t i = 0; i < n; ++i) {
        std::string s, t;
        std::cin >> s >> t;

        w.emplace_back(i, s, t);
    }

    std::sort(w.begin(), w.end());

    std::vector<std::pair<std::string, unsigned>> c;
    for (const Person& p : w) {
        if (c.empty() || p.t < c.back().second)
            c.emplace_back(p.s, p.t);
    }

    std::sort(c.begin(), c.end());

    std::cout << c.size() << '\n';
    for (const std::pair<std::string, unsigned>& x : c)
        std::cout << x.first << '\n';

    return 0;
}
