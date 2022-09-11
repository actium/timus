#include <iostream>
#include <vector>

void solve(const std::vector<int>& s, int n)
{
    const size_t m = s.size();

    long long t = 0;
    for (size_t i = 0; i < m; ++i) {
        t += s[i];

        if (t > 3ll * n) {
            std::cout << "Free after " << 1+i << " times." << '\n';
            return;
        }
    }

    std::cout << "Team.GOV!" << '\n';
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<int> s(m);
    for (int i = 0; i < m; ++i)
        std::cin >> s[i];

    solve(s, n);

    return 0;
}
