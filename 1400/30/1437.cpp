#include <array>
#include <iostream>
#include <queue>
#include <unordered_set>

int main()
{
    unsigned c[3];
    std::cin >> c[0] >> c[1] >> c[2];

    std::unordered_set<unsigned> s;
    std::queue<unsigned> q;

    const auto enqueue = [&](unsigned x, unsigned y, unsigned z) {
        const unsigned state = x << 16 | y << 8 | z;
        if (s.insert(state).second)
            q.push(state);
    };

    const auto decompose = [](unsigned x) {
        std::array<unsigned, 3> v;
        v[0] = x >> 16 & 0xFF;
        v[1] = x >> 8 & 0xFF;
        v[2] = x & 0xFF;
        return v;
    };

    enqueue(0, 0, 0);
    while (!q.empty()) {
        const std::array<unsigned, 3> x = decompose(q.front());
        q.pop();

        if (x[0] != c[0]) {
            enqueue(c[0], x[1], x[2]);

            if (x[1] != 0)
                enqueue(x[0] + std::min<unsigned>(c[0] - x[0], x[1]), x[1] - std::min<unsigned>(c[0] - x[0], x[1]), x[2]);
            if (x[2] != 0)
                enqueue(x[0] + std::min<unsigned>(c[0] - x[0], x[2]), x[1], x[2] - std::min<unsigned>(c[0] - x[0], x[2]));
        }
        if (x[1] != c[1]) {
            enqueue(x[0], c[1], x[2]);

            if (x[0] != 0)
                enqueue(x[0] - std::min<unsigned>(c[1] - x[1], x[0]), x[1] + std::min<unsigned>(c[1] - x[1], x[0]), x[2]);
            if (x[2] != 0)
                enqueue(x[0], x[1] + std::min<unsigned>(c[1] - x[1], x[2]), x[2] - std::min<unsigned>(c[1] - x[1], x[2]));
        }
        if (x[2] != c[2]) {
            enqueue(x[0], x[1], c[2]);

            if (x[0] != 0)
                enqueue(x[0] - std::min<unsigned>(c[2] - x[2], x[0]), x[1], x[2] + std::min<unsigned>(c[2] - x[2], x[0]));
            if (x[1] != 0)
                enqueue(x[0], x[1] - std::min<unsigned>(c[2] - x[2], x[1]), x[2] + std::min<unsigned>(c[2] - x[2], x[1]));
        }
    }

    bool p[768] = {};
    for (const unsigned x : s) {
        const std::array<unsigned, 3> v = decompose(x);

        p[v[0]] = true;
        p[v[1]] = true;
        p[v[2]] = true;

        p[v[0] + v[1]] = true;
        p[v[1] + v[2]] = true;
        p[v[2] + v[0]] = true;

        p[v[0] + v[1] + v[2]] = true;
    }

    unsigned k = 0;
    for (size_t i = 1; i < 768; ++i)
        k += p[i];

    std::cout << k << '\n';

    return 0;
}