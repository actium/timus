#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::vector<unsigned> s;
    for (size_t i = 0, j = 0; i < n; ++i) {
        for (s.push_back(1 + i); !s.empty() && s.back() == a[j]; s.pop_back())
            ++j;
    }

    if (s.empty())
        std::cout << "Not a proof" << '\n';
    else
        std::cout << "Cheater" << '\n';

    return 0;
}
