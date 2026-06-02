#include <iostream>
#include <string>

void ambiguity()
{
    std::cout << "Ambiguity" << '\n';
}

void impossible()
{
    std::cout << "Impossible" << '\n';
}

template <typename Selector>
bool solve(std::string& p, std::string& q, std::string& x, Selector&& select)
{
    const size_t m = x.size();

    for (size_t i = 0; i < m; ++i) {
        const size_t j = select(i);

        if (p[j] != '?' && q[j] != '?') {
            const char b = p[j] ^ (q[j] - '0');
            if (x[j] == '?')
                x[j] = b;

            if (x[j] != b)
                return false;
        }

        if (p[j] != '?' && x[j] != '?') {
            const char b = p[j] ^ (x[j] - '0');
            if (q[j] == '?')
                q[j] = b;

            if (q[j] != b)
                return false;

            if (j != 0 && p[j-1] == '?')
                p[j-1] = b;

            if (j != 0 && p[j-1] != b)
                return false;
        }

        if (x[j] != '?' && q[j] != '?') {
            const char b = x[j] ^ (q[j] - '0');
            if (p[j] == '?')
                p[j] = b;

            if (p[j] != b)
                return false;

            if (q[j+1] == '?')
                q[j+1] = b;

            if (q[j+1] != b)
                return false;
        }
    }
    return true;
}

void solve(std::string& p, std::string& x)
{
    const size_t m = x.size();

    std::string q = '0' + p;

    if (!solve(p, q, x, [m](size_t i) { return m-1-i; }))
        return impossible();

    if (!solve(p, q, x, [](size_t i) { return i; }))
        return impossible();

    if (p.find('?') != std::string::npos || x.find('?') != std::string::npos)
        return ambiguity();

    std::cout << p << '\n';
    std::cout << x << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string p, x;
    std::cin >> p >> x;

    solve(p, x);

    return 0;
}
