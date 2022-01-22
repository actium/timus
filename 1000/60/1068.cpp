#include <iostream>

void solve(int ub)
{
    int lb = 1;
    if (ub < lb)
        std::swap(lb, ub);

    std::cout << (ub - lb + 1ll) * (ub + lb) / 2 << '\n';
}

int main()
{
    int n;
    std::cin >> n;

    solve(n);

    return 0;
}
