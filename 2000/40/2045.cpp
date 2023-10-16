#include <iostream>
#include <string>

void solve(unsigned n)
{
    if (n == 1) {
        std::cout << "1 : a\n";
        return;
    }

    if (n == 2) {
        std::cout << "1 : NO\n";
        std::cout << "2 : aa\n";
        return;
    }

    const unsigned k = (n + 1) / 2;

    for (unsigned i = 1; i < 3; ++i)
        std::cout << i << " : NO\n";

    for (unsigned i = 3; i <= k; ++i) {
        std::string s(n, 'a');

        for (size_t j = 0; j < n; j += i)
            s[j] = 'b';

        for (size_t j = i - 1; j < n; j += i)
            s[j] = 'c';

        std::cout << i << " : " << s << '\n';
    }

    std::string s(n, 'a');
    for (unsigned i = k + 1; i < n; ++i) {
        s[n-i+0] = 'b';
        s[n-i+1] = 'c';
        s[n-i+2] = 'a';
        std::cout << i << " : " << s << '\n';
    }

    s[1] = s[2] = 'a';
    std::cout << n << " : " << s << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    solve(n);

    return 0;
}
