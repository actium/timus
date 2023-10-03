#include <iostream>
#include <set>
#include <string>

void solve(size_t n, const std::set<std::string>& s)
{
    if (n == 1 || (n == 2 && s.size() == 1)) {
        std::cout << '0' << '\n';
        return;
    }
    if (n == 2) {
        std::cout << '1' << '\n';
        std::cout << *s.begin() << '-' << *s.rbegin() << '\n';
        return;
    }
    if (s.size() != n) {
        std::cout << "Impossible" << '\n';
        return;
    }

    std::cout << n << '\n';
    for (const std::string& x : s)
        std::cout << x << "-zx" << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::set<std::string> s;
    for (size_t i = 0; i < n; ++i) {
        std::string x;
        std::cin >> x;

        s.insert(x);
    }

    solve(n, s);

    return 0;
}
