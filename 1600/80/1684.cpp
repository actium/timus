#include <iostream>
#include <string>
#include <vector>

std::vector<unsigned> pf(const std::string& s)
{
    const size_t n = s.length();

    std::vector<unsigned> p(n);
    for (size_t i = 1; i < n; ++i) {
        unsigned k = p[i-1];
        while (k > 0 && s[k] != s[i])
            k = p[k-1];

        if (s[k] == s[i])
            ++k;

        p[i] = k;
    }
    return p;
}

void solve(const std::string& s, const std::string& t)
{
    const size_t n = s.length(), m = t.length();

    const std::vector<unsigned> p = pf(s + ' ' + t);

    std::vector<std::string> z;
    for (size_t i = n + m; i > n; i -= p[i]) {
        if (p[i] == 0) {
            std::cout << "Yes" << '\n';
            return;
        }
        z.emplace_back(t.substr(i - n - p[i], p[i]));
    }

    std::cout << "No" << '\n';
    while (!z.empty()) {
        std::cout << z.back() << ' ';
        z.pop_back();
    }
}

int main()
{
    std::string s, t;
    std::cin >> s >> t;

    solve(s, t);

    return 0;
}
