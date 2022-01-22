#include <iostream>
#include <vector>

#include <cmath>

void solve(const std::vector<unsigned long long>& a)
{
    for (auto it = a.crbegin(); it != a.crend(); ++it)
        std::cout << std::fixed << std::sqrt(*it) << '\n';
}

int main()
{
    std::vector<unsigned long long> a;
    for (unsigned long long x; std::cin >> x; a.push_back(x));

    solve(a);

    return 0;
}
