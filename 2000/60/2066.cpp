#include <algorithm>
#include <iostream>

int main()
{
    int a, b, c;
    std::cin >> a >> b >> c;

    if (a > b) std::swap(a, b);
    if (b > c) std::swap(b, c);
    if (a > b) std::swap(a, b);

    std::cout << std::min({ a*b*c, a+b*c, a-b*c, a+b+c, a-b-c }) << '\n';

    return 0;
}
