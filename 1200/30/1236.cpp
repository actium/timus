#include <iostream>
#include <string>

unsigned decode(char c)
{
    return c < 'A' ? c - '0' : c - 'A' + 10;
}

void solve(const std::string& s, const std::string& t)
{
    constexpr char d[] = "0123456789ABCDEF";

    const size_t n = s.length();

    unsigned x = 0;
    for (size_t i = 0; i < n; i += 2) {
        const unsigned u = decode(s[i]) << 4 | decode(s[i+1]);
        const unsigned v = decode(t[i]) << 4 | decode(t[i+1]);

        x ^= u ^ v;

        std::cout << d[(x & 0xF0) >> 4] << d[(x & 0x0F) >> 0];
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s, t;
    std::cin >> s >> t;

    solve("20" + s, t);

    return 0;
}
