#include <iostream>
#include <string>
#include <vector>

void solve(std::string& s, unsigned k)
{
    const size_t n = s.length();

    bool t[26] = {};
    std::vector<size_t> p[2];
    for (size_t i = 0; i < n; ++i) {
        if (s[i] == '?') {
            p[i % 2].push_back(i);
            continue;
        }

        const size_t x = s[i] - 'a';
        if (k != 0 && !t[x])
            --k;

        t[x] = true;
    }

    if (p[0].size() + p[1].size() < k) {
        std::cout << -1 << '\n';
        return;
    }

    const auto check = [&](size_t x, size_t c) {
        if (p[x].empty() || t[c])
            return false;

        s[p[x].back()] = 'a' + c;
        p[x].pop_back();

        t[c] = true;
        return true;
    };

    for (size_t i = 0; k != 0; ) {
        if (check(0, 25 - i) || check(1, i))
            --k;
        else
            ++i;
    }

    for (const size_t x : p[0])
        s[x] = 'z';

    for (const size_t x : p[1])
        s[x] = 'a';

    std::cout << s << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    unsigned k;
    std::cin >> k;

    solve(s, k);

    return 0;
}
