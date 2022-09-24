#include <algorithm>
#include <iostream>
#include <vector>

void solve(const std::vector<unsigned>& a)
{
    const size_t n = a.size();

    std::vector<unsigned> b = a;
    std::sort(b.begin(), b.end());

    std::vector<unsigned> p1, p2;
    for (size_t i = 0; i < n; ++i) {
        if (a[i] != b[i])
            p1.push_back(1+i);

        if (a[i] != b[n-1-i])
            p2.push_back(1+i);
    }

    if (p1.size() > p2.size())
        std::swap(p1, p2);

    if (p1.empty()) {
        std::cout << "Nothing to do here" << '\n';
        return;
    }

    if (p1.size() == 2) {
        std::cout << "Yes" << '\n';
        std::cout << p1[0] << ' ' << p1[1] << '\n';
        return;
    }

    std::cout << "No hope" << '\n';
}

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    solve(a);

    return 0;
}
