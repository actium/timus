#include <iostream>
#include <string>

std::string convert(const std::string& t)
{
    std::string s, o, v, p;

    std::string* z = &p;
    for (const char c : t) {
        switch (c) {
            case '{': z = &o; break;
            case '}': z = &p; break;
            case '(': z = &s; break;
            case ')': z = &p; break;
            case '[': z = &v; break;
            case ']': z = &p; break;
            default:
                if (z->empty() || c != ' ' || z->back() != ' ')
                    z->push_back(std::tolower(c));
        }
    }

    if (!p.empty() && p[0] == ' ')
        p = p.substr(1);

    return p + o + ' ' + s + ' ' + v;
}

int main()
{
    std::string s;
    std::getline(std::cin, s);

    std::string t;
    {
        const size_t x = s.find(',');
        if (x != std::string::npos) {
            t = convert(s.substr(0, x)) + ", " + convert(s.substr(x + 1));
        } else {
            t = convert(s);
        }

        t[0] = std::toupper(t[0]);
    }

    std::cout << t << '\n';

    return 0;
}
