#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct Node {
    unsigned d;
    unsigned x;
    unsigned m;
};

std::string answer(unsigned d, unsigned x)
{
    std::string s;
    while (d-- > 0)
        s.push_back('1' + ((x >> d) & 1));

    return s;
}

std::string solve(unsigned n)
{
    if (n < 3)
        return std::to_string(n);

    if (n % 5 != 0) {
        std::queue<Node> q;
        q.push({1, 0, 1});
        q.push({1, 1, 2});

        std::vector<bool> v(n);
        while (!q.empty()) {
            const Node node = q.front();
            q.pop();

            for (unsigned i = 0; i < 2; ++i) {
                const unsigned m = (node.m * 10 + i + 1) % n;
                if (m == 0)
                    return answer(node.d + 1, node.x << 1 | i);

                if (!v[m]) {
                    q.push({node.d + 1, node.x << 1 | i, m});
                    v[m] = true;
                }
            }
        }
    }
    return "Impossible";
}

int main()
{
    unsigned n;
    std::cin >> n;

    std::cout << solve(n) << '\n';

    return 0;
}
