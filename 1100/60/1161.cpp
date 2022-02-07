#include <iostream>
#include <queue>

#include <cmath>

int main()
{
    size_t n;
    std::cin >> n;

    std::priority_queue<double> q;
    for (size_t i = 0; i < n; ++i) {
        unsigned w;
        std::cin >> w;

        q.push(w);
    }

    while (q.size() > 1) {
        const double x = q.top(); q.pop();
        const double y = q.top(); q.pop();

        q.push(2 * sqrt(x * y));
    }

    std::cout << std::fixed << q.top() << '\n';

    return 0;
}
