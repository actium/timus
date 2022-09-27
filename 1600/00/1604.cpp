#include <iostream>
#include <queue>

int main()
{
    size_t k;
    std::cin >> k;

    std::priority_queue<std::pair<unsigned, unsigned>> q;
    for (size_t i = 0; i < k; ++i) {
        unsigned n;
        std::cin >> n;

        q.emplace(n, 1+i);
    }

    const auto pull = [&q] {
        const std::pair<unsigned, unsigned> x = q.top();
        q.pop();
        return x;
    };

    std::pair<unsigned, unsigned> x = pull();
    while (!q.empty()) {
        const std::pair<unsigned, unsigned> y = pull();

        std::cout << x.second << ' ';
        if (--x.first != 0)
            q.emplace(x);

        x = y;
    }
    while (x.first != 0) {
        std::cout << x.second << ' ';
        --x.first;
    }

    return 0;
}
