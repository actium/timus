#include <iostream>

int main()
{
    unsigned w1, w2, t1, t2;
    std::cin >> w1 >> w2 >> t1 >> t2;

    if (t1 < t2)
        std::cout << (t2 - t1) * (w1 + w2 + w2) - w1 << '\n';
    else
        std::cout << (t1 - t2) * (w1 + w2 + w2) + w1 << '\n';

    return 0;
}
