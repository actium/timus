#include <iostream>
#include <string>

bool is_suffix_palindromic(const std::string& s, size_t i)
{
    for (size_t j = s.length() - 1; i < j; ++i, --j) {
        if (s[i] != s[j])
            return false;
    }
    return true;
}

int main()
{
    std::string s;
    std::cin >> s;

    size_t k = 1;
    while (k < s.length() && !is_suffix_palindromic(s, k))
        ++k;

    const std::string t = s.substr(0, k);

    std::cout << s << std::string(t.crbegin(), t.crend()) << '\n';

    return 0;
}
