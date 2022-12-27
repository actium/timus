#include <iostream>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n;
    std::cin >> n;

    std::vector<long long> s(n + 1);
    for (size_t i = 0; i <= n; ++i) {
        unsigned a, b, c;
        std::cin >> a >> b >> c;

        s[a-1] += c;
        s[b] -= c;
    }

    for (size_t i = 0; i < n; ++i) {
        std::cout << s[i] << ' ';

        s[i+1] += s[i];
    }

    return 0;
}
