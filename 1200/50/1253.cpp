#include <iostream>
#include <string>
#include <vector>

bool solve(std::vector<std::string>& s, size_t u, std::vector<unsigned>& v)
{
    v[u] = 1;
    {
        std::string t;
        for (size_t i = 1; s[u][i] != '#'; ++i) {
            if (s[u][i] == '*') {
                const size_t x = s[u][++i] - '1';
                if (v[x] == 0 && !solve(s, x, v) || v[x] == 1)
                    return false;

                t.append(s[x]);
            } else {
                t.push_back(s[u][i]);
            }
        }
        s[u] = t;
    }
    v[u] = 2;

    return s[u].length() <= 1000000;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n >> std::ws;

    std::vector<std::string> s(n);
    for (size_t i = 0; i < n; ++i) {
        std::string t;
        do {
            s[i].push_back('\n');
            std::getline(std::cin, t);
            s[i].append(t);
        } while (s[i].back() != '#');
    }

    std::vector<unsigned> v(n);
    std::cout << (solve(s, 0, v) ? s[0] : "#") << '\n';

    return 0;
}
