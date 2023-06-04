#include <iostream>
#include <string>

void solve(const std::string& s, size_t n, size_t m)
{
    const size_t k = s.length();

    unsigned c = 1;
    for (size_t i = 0, j = 0, x = k; i < k; ++i) {
        if (s[i] != ' ' && !std::isalpha(s[i]))
            x = i;

        if (i - j + 1 < n)
            continue;

        if (x <= i) {
            j += std::max(x - j, n);
            i = j - 1;
            x = k;
            c += (j < k);
        }
        if (i - j + 1 == m) {
            j = i + 1;
            c += (j < k);
        }
    }

    std::cout << c << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m >> std::ws;

    std::string s;
    std::getline(std::cin, s);

    solve(s, n, m);

    return 0;
}
