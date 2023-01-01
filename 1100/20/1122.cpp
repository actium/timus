#include <iostream>
#include <queue>

int main()
{
    char s[16];
    for (size_t i = 0; i < 16; ++i)
        std::cin >> s[i];

    char t[12];
    for (size_t i = 0; i < 12; ++i) {
        if (i % 4 != 3)
            std::cin >> t[i];
    }

    uint16_t b = 0;
    for (size_t i = 0; i < 16; ++i) {
        if (s[i] == 'W')
            b |= 1 << (15 - i);
    }

    unsigned o = 0;
    for (size_t i = 0; i < 12; ++i) {
        if (i % 4 != 3 && t[i] == '1')
            o |= 1 << (15 - i);
    }

    const unsigned m[16] = {
        (o << 5) & 0xCC00, (o << 4) & 0xEE00, (o << 3) & 0x7700, (o << 2) & 0x3300,
        (o << 1) & 0xCCC0, (o << 0) & 0xEEE0, (o >> 1) & 0x7770, (o >> 2) & 0x3330,
        (o >> 3) & 0x0CCC, (o >> 4) & 0x0EEE, (o >> 5) & 0x0777, (o >> 6) & 0x0333,
        (o >> 7) & 0x00CC, (o >> 8) & 0x00EE, (o >> 9) & 0x0077, (o >> 10) & 0x0033
    };

    std::queue<std::pair<uint16_t, unsigned>> q;
    bool v[65536] = {};

    const auto enqueue = [&](uint16_t x, unsigned t) {
        if (!v[x]) {
            q.emplace(x, t);
            v[x] = true;
        }
    };

    for (enqueue(b, 0); !q.empty(); q.pop()) {
        const auto x = q.front();
        if (x.first == 0 || x.first == 65535)
            break;

        for (size_t i = 0; i < 16; ++i)
            enqueue(x.first ^ m[i], x.second + 1);
    }

    if (q.empty()) {
        std::cout << "Impossible" << '\n';
    } else {
        std::cout << q.front().second << '\n';
    }

    return 0;
}
