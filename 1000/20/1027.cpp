#include <iostream>
#include <string>
#include <vector>

bool valid_expression_symbol(char c)
{
    return c == '(' || c == ')' || c == '=' || c == '+' || c == '-' || c == '*' || c == '/' || isdigit(c);
}

bool validate(const std::string& t)
{
    const size_t n = t.length();

    std::vector<std::pair<unsigned, unsigned>> states;
    states.emplace_back(0, 0);
    for (size_t i = 0; i < n; ++i) {
        if (t[i] == '\r' || t[i] == '\n')
            continue;

        if (states.back().first != 1 && t[i] == '(' && i + 1 < n && t[i+1] == '*') {
            states.emplace_back(1, 0);
            ++i;
            continue;
        }

        if (states.back().first == 1 && t[i] == '*' && i + 1 < n && t[i+1] == ')') {
            states.pop_back();
            ++i;
            continue;
        }

        if (states.back().first == 2 && !valid_expression_symbol(t[i]))
            return false;

        if (states.back().first == 0 && t[i] == '(')
            states.emplace_back(2, 0);

        if (states.back().first == 0 && t[i] == ')')
            return false;

        if (states.back().first == 2 && t[i] == '(') {
            ++states.back().second;
            continue;
        }
        if (states.back().first == 2 && t[i] == ')') {
            if (states.back().second == 0)
                return false;

            if (--states.back().second == 0)
                states.pop_back();
        }
    }

    return states.size() == 1 && states.back().first == 0;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string t;
    for (std::string s; std::getline(std::cin, s); t.append(s));

    std::cout << (validate(t) ? "YES" : "NO") << '\n';

    return 0;
}
