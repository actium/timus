#include <iostream>
#include <queue>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned v[1 + 30000] = {};

    std::priority_queue<unsigned, std::vector<unsigned>, std::greater<unsigned>> p;
    for (unsigned i = 1; i <= 30000; ++i)
        p.push(i);

    std::queue<std::pair<unsigned, unsigned>> q;

    const auto update = [&](unsigned t) {
        while (!q.empty() && q.front().second <= t) {
            const auto [x, y] = q.front();
            q.pop();

            if (v[x] == y) {
                v[x] = 0;
                p.push(x);
            }
        }
    };

    const auto allocate = [&](unsigned t) {
        const unsigned x = p.top();
        p.pop();

        v[x] = t + 600;
        q.emplace(x, v[x]);

        std::cout << x << '\n';
    };

    const auto access = [&](unsigned t, unsigned x) {
        if (v[x] != 0) {
            v[x] = t + 600;
            q.emplace(x, v[x]);

            std::cout << '+' << '\n';
        } else {
            std::cout << '-' << '\n';
        }
    };

    unsigned t;
    char r;
    while (std::cin >> t >> r) {
        update(t);

        if (r == '+') {
            allocate(t);
        } else  {
            unsigned x;
            std::cin >> x;

            access(t, x);
        }
    }

    return 0;
}
