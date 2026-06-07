#include <iostream>
#include <string>
#include <vector>

size_t index(char c)
{
    return c == 'W' ? 0 : c == 'M' ? 1 : c == 'C' ? 2 : 3;
}

bool search(const std::vector<std::string>& c, size_t u, std::vector<bool>& used, int matches[4])
{
    if (used[u])
        return false;

    used[u] = true;

    for (const char q : c[u]) {
        const size_t v = index(q);
        if (matches[v] == -1 || search(c, matches[v], used, matches)) {
            matches[v] = u;
            return true;
        }
    }
    return false;
}

unsigned match(const std::vector<std::string>& c)
{
    const size_t n = c.size();

    int matches[4] = { -1, -1, -1, -1 };
    for (size_t i = 0; i < n; ++i) {
        std::vector<bool> used(n);
        search(c, i, used, matches);
    }

    unsigned k = 0;
    for (size_t i = 0; i < 4; ++i)
        k += (matches[i] != -1);

    return k;
}

void solve(std::vector<std::string>& c)
{
    const unsigned k = match(c);
    std::cout << k << '\n';

    if (k < 4) {
        std::cout << "Looking for";
        for (const auto q : { "warrior", "mage", "cleric", "rogue" }) {
            c.emplace_back(1, std::toupper(q[0]));

            if (match(c) > k)
                std::cout << ' ' << q;

            c.pop_back();
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::string> c(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> c[i];

    solve(c);

    return 0;
}
