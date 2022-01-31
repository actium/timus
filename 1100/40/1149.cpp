#include <iostream>
#include <string>
#include <vector>

int main()
{
    constexpr char c[2] = { '+', '-' };

    unsigned n;
    std::cin >> n;

    std::vector<std::string> a(n);
    {
        a[0] = "sin(1";

        for (size_t i = 1; i < n; ++i)
            a[i] = a[i-1] + c[i%2] + "sin(" + std::to_string(1+i);

        for (size_t i = 0; i < n; ++i)
            a[i].append(i+1, ')');
    }

    std::string s = a[0] + "+" + std::to_string(n);
    for (size_t i = 1; i < n; ++i)
        s = "(" + s + ")" + a[i] + "+" + std::to_string(n - i);

    std::cout << s << '\n';

    return 0;
}
