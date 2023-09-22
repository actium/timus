#include <iostream>

void solve(char w, unsigned m, unsigned c)
{
    unsigned lb = 0, ub = 0;

    if (w == 'h') {
        if (m <= c) {
            lb = c - m;
            lb += (lb < c);
        }

        const unsigned d = 30 + c - m;
        ub = std::min<unsigned>(30, d - (d > c));
    } else {
        if (m < c)
            lb = c - m;

        const unsigned d = 30 + c - m;
        ub = std::min<unsigned>(30, d + (d < c));
    }

    std::cout << lb << ' ' << ub << '\n';
}

void test_case()
{
    std::string s;
    std::getline(std::cin, s);

    const auto score = [&](size_t x) {
        x = s.find("goals", x);
        return std::stoi(s.substr(x - 3, 3));
    };

    solve(s[26], score(46), score(68));
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t t;
    std::cin >> t >> std::ws;

    while (t-- > 0)
        test_case();

    return 0;
}
