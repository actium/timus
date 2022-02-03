#include <iostream>
#include <string>

int main()
{
    std::string s;
    std::cin >> s;

    const size_t n = s.length();

    const auto search = [&](int l, int r) {
        while (l >= 0 && r < n && s[l] == s[r])
            --l, ++r;

        return s.substr(l+1, r-l-1);
    };

    std::string p;
    for (size_t i = 0; i < n; ++i) {
        const std::string c = search(i, i);
        if (c.length() > p.length())
            p = c;

        if (i > 0) {
            const std::string c = search(i-1, i);
            if (c.length() > p.length())
                p = c;
        }
    }

    std::cout << p << '\n';

    return 0;
}
