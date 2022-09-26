#include <iostream>
#include <string>
#include <set>

size_t lcp(const std::string& s, const std::string& t)
{
    const size_t n = std::min(s.length(), t.length());

    size_t k = 0;
    while (k < n && s[k] == t[k])
        ++k;
    
    return k;
}

int main()
{
    std::string s;
    std::cin >> s;

    const size_t n = s.length();

    std::set<std::string> u;
    for (size_t i = 0; i < n; ++i)
        u.insert(s.substr(i));

    const unsigned b = u.size() + 1;

    unsigned k = b - u.begin()->length();
    for (auto si = u.begin(), ti = std::next(si); ti != u.end(); si = ti++)
        k += b - ti->length() - lcp(*si, *ti);

    std::cout << k << '\n';

    return 0;
}
