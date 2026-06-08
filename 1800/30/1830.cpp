#include <iostream>
#include <string>

using integer = unsigned long long;

integer prepare_update(std::string& s, size_t x, char d)
{
    if (x == 0) {
        if (s[x] == d)
            return 0;

        s[x] = d;
        return 1;
    }

    if (s[x] != d) {
        const integer k = prepare_update(s, x-1, '1') + (1ull << x);
        s[x] = d;
        s[x-1] = '0';
        return k;
    }

    return prepare_update(s, x-1, '0');
}

integer set(std::string& s, size_t x, char d)
{
    if (s[x] == d)
        return 0;

    if (x == 0)
        return 1;

    return prepare_update(s, x-1, '1') + 1;
}

integer solve(std::string& s, std::string& t)
{
    integer k = 0;
    for (size_t i = s.size() - 1; ~i != 0; --i)
        k += set(s, i, t[i]);

    return k;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::string s, t;
    std::cin >> s >> t;

    std::cout << solve(s, t) << '\n';

    return 0;
}
