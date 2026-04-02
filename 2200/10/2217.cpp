#include <iostream>
#include <string>

const char* solve(std::string& s, size_t lx, size_t rx)
{
    if (lx >= rx)
        return "YES";

    if (s[lx] == s[rx])
        return solve(s, lx+1, rx-1);

    if (s[rx] == '1')
        return "NO";

    const size_t mx = (lx + rx) / 2;

    size_t x1 = rx;
    while (x1 >= mx && s[x1] == '0')
        --x1;

    if (x1 >= mx) {
        std::swap(s[x1], s[rx]);
        return solve(s, lx, rx);
    }

    size_t x2 = lx;
    while (x2 <= mx && s[x2] == '1')
        ++x2;

    if (x2 <= mx) {
        std::swap(s[lx], s[x2]);
        return solve(s, lx, rx);
    }

    return "NO";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    std::cout << solve(s, 0, n-1) << '\n';

    return 0;
}
