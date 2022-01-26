#include <iostream>
#include <vector>

void solve(unsigned k, const std::vector<unsigned>& a)
{
    unsigned r = 0;
    for (const unsigned x : a) {
        r += x;
        r -= std::min(r, k);
    }

    std::cout << r << '\n';
}

int main()
{
    unsigned k, n;
    std::cin >> k >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    solve(k, a);

    return 0;
}
