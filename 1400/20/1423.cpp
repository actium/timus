#include <iostream>
#include <string>
#include <vector>

size_t search(const std::string& s, const std::string& t)
{
    const size_t n = s.length();

    std::vector<size_t> p(n);
    for (size_t i = 1; i < n; ++i) {
        size_t j = p[i-1];
        while (j > 0 && t[j] != t[i])
            j = p[j-1];

        if (t[j] == t[i])
            ++j;

        p[i] = j;
    }

    for (size_t i = 0, j = 0; i < 2 * n; ++i) {
        while (j > 0 && t[j] != s[i%n])
            j = p[j-1];

        if (t[j] == s[i%n])
            ++j;

        if (j == n)
            return 2 * n - i - 1;
    }

    return std::string::npos;
}

int main()
{
    size_t n;
    std::cin >> n;

    std::string s, t;
    std::cin >> s >> t;

    const size_t x = search(s, t);
    if (x == std::string::npos) {
        std::cout << -1 << '\n';
    } else {
        std::cout << x % n << '\n';
    }

    return 0;
}
