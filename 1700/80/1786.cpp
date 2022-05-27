#include <iostream>
#include <string>

unsigned count(const std::string& s, size_t i)
{
    constexpr char t[] = "Sandro";

    unsigned k = 0;
    for (size_t j = 0; j < 6; ++j) {
        k += (tolower(s[i+j]) != tolower(t[j]));
        k += (isupper(s[i+j]) != isupper(t[j]));
    }
    return k;
}

int main()
{
    std::string s;
    std::cin >> s;

    unsigned k = ~0u;
    for (size_t i = 5; i < s.length(); ++i)
        k = std::min(k, count(s, i - 5));

    std::cout << k * 5 << '\n';

    return 0;
}
