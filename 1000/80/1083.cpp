#include <iostream>

void solve(unsigned n, unsigned k)
{
    unsigned f = 1;
    for (int x = n; x > 0; x -= k)
        f *= x;

    std::cout << f << '\n';
}

int main()
{
    unsigned n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    solve(n, s.length());

    return 0;
}
