#include <iomanip>
#include <iostream>
#include <set>
#include <string>
#include <vector>

std::set<unsigned> solve(unsigned n)
{
    std::set<unsigned> s;
    s.insert(n - n / 11);
    if (n >= 10 && n % 2 == 0) {
        const unsigned d = n % 10 / 2;

        for (const unsigned x : solve(n / 10))
            s.insert(x * 10 + d);

        for (const unsigned x : solve(n / 10 - 1))
            s.insert(x * 10 + d + 5);
    }
    return s;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::set<unsigned> s = solve(n);
    for (auto it = s.begin(); it != s.end(); ) {
        unsigned x = *it, y = n - x;
        while (x >= 10 && x % 10 == y % 10) {
            x /= 10;
            y /= 10;
        }
        x / 10 != y ? it = s.erase(it) : ++it;
    }

    std::cout << s.size() << '\n';
    for (const unsigned x : s) {
        const std::string t = std::to_string(x);
        std::cout << x << " + " << std::setfill('0') << std::setw(t.length() - 1) << n - x << " = " << n << '\n';
    }

    return 0;
}
