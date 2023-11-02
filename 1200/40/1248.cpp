#include <iostream>
#include <string>

std::string prepare(const std::string& s)
{
    size_t x = s.find('e');
    if (x == std::string::npos)
        x = s.find('E');

    const int e = std::stoi(s.substr(x + 1));

    std::string v(222, '0');
    v[118 + e] = s[0];
    for (size_t i = 1 + (s[1] == '.'), j = 117 + e; i < x; ++i, --j)
        v[j] = s[i];

    return v;
}

void add(std::string& v, const std::string& d)
{
    for (size_t i = 0; i < 221; ++i) {
        v[i] += d[i] - '0';

        if (v[i] > '9') {
            v[i] -= 10;
            v[i+1] += 1;
        }
    }
}

int main()
{
    size_t n;
    std::cin >> n;

    std::string v(222, '0');
    for (size_t i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;

        add(v, prepare(s));
    }

    int e = 103;
    while (v.back() == '0') {
        v.pop_back();
        --e;
    }

    std::cout << v.back() << '.';
    for (size_t i = 0; i < 18; ++i) {
        v.pop_back();
        std::cout << v.back();
    }
    std::cout << 'e' << e << '\n';

    return 0;
}
