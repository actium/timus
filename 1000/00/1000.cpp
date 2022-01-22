#include <iostream>

void solve(int a, int b)
{
    std::cout << a + b << '\n';
}

int main()
{
    int a, b;
    std::cin >> a >> b;

    solve(a, b);

    return 0;
}
