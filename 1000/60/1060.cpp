#include <iostream>
#include <queue>

int main()
{
    char s[16];
    for (size_t i = 0; i < 16; ++i)
        std::cin >> s[i];

    uint16_t b = 0;
    for (size_t i = 0; i < 16; ++i) {
        if (s[i] == 'w')
            b |= 1 << (15 - i);
    }

    const unsigned m[16] = {
        0b1100100000000000, 0b1110010000000000, 0b0111001000000000, 0b0011000100000000,
        0b1000110010000000, 0b0100111001000000, 0b0010011100100000, 0b0001001100010000,
        0b0000100011001000, 0b0000010011100100, 0b0000001001110010, 0b0000000100110001,
        0b0000000010001100, 0b0000000001001110, 0b0000000000100111, 0b0000000000010011,
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
