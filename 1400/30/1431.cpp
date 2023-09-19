#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i];

    std::sort(s.begin(), s.end());

    for (size_t i = 0, j = 1; j < s.size(); ++j) {
        if (s[j] == s[i])
            continue;

        while (s[j] - s[i] > 1)
            ++i;

        while (j < s.size() && s[j] - s[i] == 1) {
            s.erase(s.begin() + j);
            s.erase(s.begin() + i);
            --j;
            --n;
        }
    }

    std::cout << n << '\n';

    return 0;
}
