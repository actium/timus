#include <iostream>
#include <string>

void dump(std::string& s, char t)
{
    while (!s.empty()) {
        std::cout << s.back();
        s.pop_back();
    }

    std::cout << t;
}

void solve(const std::string& s)
{
    std::string t;
    for (const char c : s) {
        if (isalpha(c)) {
            t.push_back(c);
        } else {
            dump(t, c);
        }
    }

    dump(t, '\n');
}

int main()
{
    for (std::string s; std::getline(std::cin, s); solve(s));

    return 0;
}
