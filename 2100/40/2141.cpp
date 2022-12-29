#include <iostream>
#include <vector>

long long solve(std::vector<int>::iterator b, std::vector<int>::iterator e)
{
    long long s = 0, lb = 0, r = 0, x = 0;
    for (auto it = b; it != e; ++it) {
        if (x == 0) {
            s += *it;
        } else {
            s -= *it;
            lb = std::min(lb, s);
        }
        r = std::max(r, s - lb);
        x ^= 1;
    }
    return r;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<int> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    const auto c1 = solve(a.begin(), a.end());
    const auto c2 = solve(++a.begin(), a.end());

    std::cout << std::max(c1, c2) << '\n';

    return 0;
}
