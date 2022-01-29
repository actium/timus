#include <iostream>
#include <string>

int main()
{
    std::string s;
    std::cin >> s;

    std::string t;
    for (const char c : s) {
        if (!t.empty() && c == t.back())
            t.pop_back();
        else
            t.push_back(c);
    }

    std::cout << t << '\n';

    return 0;
}
