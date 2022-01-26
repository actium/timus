#include <iostream>

int main()
{
    unsigned n, m;
    std::cin >> n >> m;

    std::cout << ((n * m - 1) % 2 == 0 ? "[second]=:]" : "[:=[first]") << '\n';

    return 0;
}
