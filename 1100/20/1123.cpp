#include <iostream>
#include <string>

bool suffix_is_greater(const std::string& s)
{
    const size_t n = s.length(), k = n / 2;

    const std::string x = s.substr(0, k);
    const std::string y = s.substr(n - k);

    return std::string(x.crbegin(), x.crend()) < y;
}

int main()
{
    std::string s;
    std::cin >> s;

    const size_t n = s.length();

    if (suffix_is_greater(s)) {
        for (size_t i = (n - 1) / 2; ++s[i] > '9'; --i)
            s[i] = '0';
    }

    for (size_t i = (n + 1) / 2; i < n; ++i)
        s[i] = s[n-1-i];

    std::cout << s << '\n';

    return 0;
}
