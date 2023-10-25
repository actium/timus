#include <iostream>
#include <vector>

void solve(const std::vector<unsigned>& a)
{
    using integer = unsigned long long;

    const size_t n = a.size();

    std::vector<size_t> b[2];
    for (size_t i = 0; i < n; ++i) {
        const size_t j = (i + 1) % n;
        if (a[i] < a[j] || a[i] == a[j] && b[0].empty())
            b[0].push_back(i);
        else
            b[1].push_back(i);
    }

    std::cout << "YES" << '\n';
    for (size_t i = 0; i < 2; ++i) {
        std::cout << b[i].size() << '\n';
        for (const size_t x : b[i])
            std::cout << 1 + x << ' ';
        std::cout << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    solve(a);

    return 0;
}
