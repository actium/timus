#include <iostream>
#include <queue>
#include <vector>

using integer = unsigned long long;

struct Node {
    unsigned value = 0;
    unsigned count = 0;

    Node* links[2] = {};
};

integer solve(const std::vector<unsigned>& a)
{
    const size_t n = a.size();

    std::vector<Node> p(1+n+1);
    p.front().links[1] = &p[1];
    for (size_t i = 1; i <= n; ++i) {
        p[i].value = a[i-1];
        p[i].count = 1;
        p[i].links[0] = &p[i-1];
        p[i].links[1] = &p[i+1];
    }
    p.back().links[0] = &p[n];

    std::priority_queue<std::pair<unsigned, size_t>> q;
    for (size_t i = 1; i <= n; ++i)
        q.emplace(p[i].value, i);

    integer k = 0;
    while (!q.empty()) {
        const size_t index = q.top().second;
        q.pop();

        const auto m = &p[index], l = m->links[0], r = m->links[1];

        if (l->value == m->value) {
            l->count += m->count;
            l->links[1] = r;
            r->links[0] = l;
        } else {
            const unsigned d = m->value - std::max(l->value, r->value);
            if (d < m->value) {
                m->value -= d;
                q.emplace(m->value, index);
            }
            k += integer(m->count + 1) / 2 * d;
        }
    }
    return k;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    std::cout << solve(a) << '\n';

    return 0;
}
