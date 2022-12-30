#include <iostream>
#include <vector>

const char* solve(const std::vector<unsigned>& a, unsigned n)
{
    const size_t s = a.size();

    std::vector<unsigned> p(1 + s);
    for (size_t i = 0; i < s; ++i)
        p[1+i] = p[i] + a[i];

    for (size_t i = 0; i < s; ++i) {
        if (p[i+1] > i + 1 + n)
            return "NO";

        if (p[s] - p[i] > s - i + n)
            return "NO";
    }

    return "YES";
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t s;
    std::cin >> s;

    unsigned n;
    std::cin >> n;

    std::vector<unsigned> a(s);
    for (size_t i = 0; i < s; ++i)
        std::cin >> a[i];

    std::cout << solve(a, n) << '\n';

    return 0;
}
