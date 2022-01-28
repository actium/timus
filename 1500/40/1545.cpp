#include <iostream>

int main()
{
    unsigned n;
    std::cin >> n;

    bool t[26][26] = {};
    while (n-- > 0) {
        char a, b;
        std::cin >> a >> b;

        t[a-'a'][b-'a'] = true;
    }

    char x;
    std::cin >> x;

    for (size_t i = 0; i < 26; ++i) {
        if (t[x-'a'][i])
            std::cout << x << char('a' + i) << '\n';
    }

    return 0;
}
