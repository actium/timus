#include <array>
#include <iostream>
#include <string>
#include <vector>

struct Node {
    unsigned p = 0;
    unsigned d[2] = {};
    int b = 0;
};

void solve(const std::string& s, const std::string& t)
{
    const size_t n = s.length();

    std::vector<Node> q(1);

    std::vector<std::vector<std::array<unsigned, 3>>> v(1+n, std::vector<std::array<unsigned, 3>>(1+n));

    const auto enqueue = [&](size_t p, unsigned x) {
        Node node = q[p];
        if (node.d[x] == n)
            return;

        const char c = (x == 0 ? s[node.d[0]] : t[node.d[1]]);
        node.b += (c == '0' ? -1 : +1);
        if (node.b < -1 || node.b > +1)
            return;

        ++node.d[x];

        if (v[node.d[0]][node.d[1]][1+node.b] == 0) {
            v[node.d[0]][node.d[1]][1+node.b] = q.size();
            node.p = p;
            q.push_back(node);
        }
    };

    for (size_t i = 0; i < q.size(); ++i) {
        enqueue(i, 0);
        enqueue(i, 1);
    }

    size_t x = 0;
    while (x < 3 && v[n][n][x] == 0)
        ++x;

    if (x == 3) {
        std::cout << "Impossible" << '\n';
    } else {
        std::string r;
        for (size_t i = v[n][n][x]; i != 0; i = q[i].p) {
            const Node& node = q[i];
            r.push_back(node.d[0] > q[node.p].d[0] ? '1' : '2');
        }

        for (auto it = r.rbegin(); it != r.rend(); ++it)
            std::cout << *it;
    }
}

int main()
{
    size_t n;
    std::cin >> n;

    std::string s, t;
    std::cin >> s >> t;

    solve(s, t);

    return 0;
}
