#include <iostream>
#include <string>

constexpr unsigned t[] = {
     0,  1,  2,  5,  5,  5,  5,  7,  7,  7,  7,  9,  9,  9,  9, 10,
    10, 10, 10, 11, 11, 11, 11, 13, 13, 13, 13, 13, 13, 13, 13, 13,
};

unsigned solve(std::string& n)
{
    const size_t k = n.length();

    if (k < 6) {
        unsigned x = 0;
        for (size_t i = 0; i < k; ++i) {
            x *= 2;
            x += n[i] - '0';
        }
        return t[x];
    }

    bool h = (n.end()[-3] == '1' && n.end()[-2] == '1' && n.end()[-1] == '1');
    if (!h) {
        size_t x = 1;
        while (x < k && n[x] == '0')
            ++x;

        h = (x < k - 3);
    }

    return k * 3 - (h ? 2 : 5);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string n;
    std::cin >> n;

    std::cout << solve(n) << '\n';

    return 0;
}
