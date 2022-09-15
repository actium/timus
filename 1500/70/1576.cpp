#include <iostream>
#include <string>

unsigned digit(char c)
{
    return c - '0';
}

int main()
{
    unsigned n1, c1;
    std::cin >> n1 >> c1;

    unsigned n2, t, c2;
    std::cin >> n2 >> t >> c2;

    unsigned n3;
    std::cin >> n3;

    unsigned k;
    std::cin >> k;

    unsigned m = 0;
    for (unsigned i = 0; i < k; ++i) {
        std::string s;
        std::cin >> s;

        const unsigned d = digit(s[0]) * 600 + digit(s[1]) * 60 + digit(s[3]) * 10 + digit(s[4]);
        if (d <= 6)
            continue;

        m += (d + 59) / 60;
    }

    std::cout << "Basic:     " << n1 + m * c1 << '\n';
    std::cout << "Combined:  " << n2 + (m > t ? m - t : 0) * c2 << '\n';
    std::cout << "Unlimited: " << n3;

    return 0;
}
