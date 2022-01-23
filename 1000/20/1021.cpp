#include <algorithm>
#include <iostream>
#include <vector>

void solve(const std::vector<int>& a, const std::vector<int>& b)
{
    const size_t n = b.size();

    for (size_t i = 0; i < n; ++i) {
        if (std::binary_search(a.cbegin(), a.cend(), 10000 - b[i])) {
            std::cout << "YES" << '\n';
            return;
        }
    }

    std::cout << "NO" << '\n';
}

std::vector<int> input()
{
    size_t n;
    std::cin >> n;

    std::vector<int> v(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> v[i];

    return v;
}

int main()
{
    const std::vector<int> a = input();
    const std::vector<int> b = input();

    solve(a, b);

    return 0;
}
