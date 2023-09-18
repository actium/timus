#include <iostream>
#include <string>

int solve(const std::string_view& a, const std::string_view& b, unsigned t)
{
    const char* const pa = a.data();
    const char* const pb = b.data();

    const size_t m = a.length();
    if (m % 2 == 0) {
        const int v1 = solve(std::string_view(pa, m / 2), std::string_view(pa + m / 2, m / 2), t ^ 1);
        const int v2 = solve(std::string_view(pb, m / 2), std::string_view(pb + m / 2, m / 2), t ^ 1);
        return -std::min(v1, v2);
    }

    for (size_t i = 0; i < m; ++i) {
        if (pa[i] != pa[0] || pb[i] != pa[0])
            return 0;
    }
    return (pa[0] == 'A' + t) ? +1 : -1;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::string a, b;
    std::cin >> a >> b;

    switch (solve(a, b, 0)) {
        case -1:
            std::cout << "Bob" << '\n';
            break;

        case 0:
            std::cout << "Draw" << '\n';
            break;

        case +1:
            std::cout << "Alice" << '\n';
            break;
    }

    return 0;
}
