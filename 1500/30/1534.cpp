#include <iostream>

unsigned maximum(unsigned k, unsigned l, unsigned n)
{
    if (k < n)
        return k * 3 + (n - k - (l != 0));

    if (l == 0 || k - (n - 1) > l)
        return n * 3;

    return (n - 1) * 3 + (k - (n - 1) == l);
}

unsigned minimum(unsigned k, unsigned l, unsigned n)
{
    if (l < n)
        return k == 0 ? n - l : 3 + (n - l - 1) - (n > 1 && k == 1);

    if (k == 0 || l - (n - 1) > k)
        return 0;

    return l - (n - 1) == k ? 1 : 3 - (n > 1 && k + n - 1 == l + 1);
}

int main()
{
    unsigned k, l, n;
    std::cin >> k >> l >> n;

    std::cout << maximum(k, l, n) << ' ' << minimum(k, l, n) << '\n';

    return 0;
}
