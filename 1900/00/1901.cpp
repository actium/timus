#include <algorithm>
#include <iostream>
#include <vector>

void solve(std::vector<unsigned>& v, unsigned s)
{
    const size_t n = v.size();

    std::sort(v.begin(), v.end());

    std::vector<unsigned> p1, p2;
    for (size_t i = 0, j = n - 1; i <= j; ++i) {
        if (i == j) {
            p1.push_back(v[i]);
            continue;
        }
        if (v[i] + v[j] > s) {
            p1.push_back(v[i]);
            p1.push_back(v[j--]);
        } else {
            p2.push_back(v[i]);
        }
    }

    std::cout << p1.size() + p2.size() / 2 << '\n';
    for (const unsigned x : p1)
        std::cout << x << ' ';
    for (const unsigned x : p2)
        std::cout << x << ' ';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    unsigned s;
    std::cin >> s;

    std::vector<unsigned> v(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> v[i];

    solve(v, s);

    return 0;
}
