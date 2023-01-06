#include <iostream>
#include <queue>
#include <string>
#include <vector>

using integer = unsigned long long;

constexpr integer oo = ~integer(0);

struct Transition {
    size_t x;
    unsigned d;
    char s;
};

void solve(const std::vector<std::vector<Transition>>& t)
{
    const size_t n = t.size();

    std::queue<std::pair<unsigned, bool>> q;
    bool in_queue[10000][2] = {};

    const auto enqueue = [&](unsigned v, bool p) {
        if (!in_queue[v][p]) {
            q.emplace(v, p);
            in_queue[v][p] = true;
        }
    };

    const auto dequeue = [&] {
        const auto x = q.front();
        q.pop();
        in_queue[x.first][x.second] = false;
        return x;
    };

    std::vector<integer> d1(n, oo), d2(n, oo);
    d1[0] = 0;
    enqueue(0, false);
    while (!q.empty()) {
        const auto x = dequeue();
        for (const auto& y : t[x.first]) {
            if (x.second) {
                if (y.s == 'L')
                    continue;

                if (d2[x.first] + y.d < d2[y.x]) {
                    d2[y.x] = d2[x.first] + y.d;
                    enqueue(y.x, true);
                }
            } else if (y.s != 'P') {
                if (d1[x.first] + y.d < d1[y.x]) {
                    d1[y.x] = d1[x.first] + y.d;
                    enqueue(y.x, false);
                }
            } else if (d1[x.first] + y.d < d2[y.x]) {
                d2[y.x] = d1[x.first] + y.d;
                enqueue(y.x, true);
            }
        }
    }

    if (d1[n-1] == oo && d2[n-1] == oo) {
        std::cout << "Offline" << '\n';
    } else {
        std::cout << "Online" << '\n';
        std::cout << std::min(d1[n-1], d2[n-1]) << '\n';
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<Transition>> t(n);
    for (size_t i = 0; i < m; ++i) {
        unsigned x, y, d;
        std::cin >> x >> y >> d;

        std::string s;
        std::cin >> s;

        t[x-1].push_back({y-1, d, s[0]});
    }

    solve(t);

    return 0;
}
