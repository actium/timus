#include <algorithm>
#include <iostream>
#include <vector>

void solve(std::vector<unsigned>& v)
{
    std::sort(v.begin(), v.end());

    unsigned x = 0;
    for (size_t i = 0, k = v.size() / 2; i <= k; ++i)
        x += (v[i] + 1) / 2;

    std::cout << x << '\n';
}

int main()
{
    size_t k;
    std::cin >> k;

    std::vector<unsigned> v(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> v[i];

    solve(v);

    return 0;
}
