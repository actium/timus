#include <iostream>
#include <map>
#include <vector>

unsigned timestamp(const std::string& t)
{
    const unsigned h = (t[0] - '0') * 10 + (t[1] - '0');
    const unsigned m = (t[3] - '0') * 10 + (t[4] - '0');
    const unsigned s = (t[6] - '0') * 10 + (t[7] - '0');
    return h * 3600 + m * 60 + s;
}

void print_time(unsigned t)
{
    const unsigned h = t / 3600;
    const unsigned m = t % 3600 / 60;
    const unsigned s = t % 60;

    std::cout << h / 10 << h % 10 << ':' << m / 10 << m % 10 << ':' << s / 10 << s % 10 << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t[4];
    for (size_t i = 0; i < 4; ++i)
        std::cin >> t[i];

    std::multimap<unsigned, size_t> q[2];

    size_t n;
    std::cin >> n;

    for (size_t i = 0; i < n; ++i) {
        std::string x;
        std::cin >> x;

        q[1].emplace(timestamp(x), i);
    }

    size_t m = 0;
    std::cin >> m;

    for (size_t i = 0; i < m; ++i) {
        std::string x;
        std::cin >> x;

        q[0].emplace(timestamp(x), n + i);
    }

    std::vector<unsigned> s(n + m);
    {
        int x[2] = { -500, -500 };

        auto it = q[0].begin(), jt = q[1].begin();
        while (it != q[0].end() && jt != q[1].end()) {
            const int u = std::max(x[1] + t[1], x[0] + t[3]), v = std::max(x[1] + t[0], x[0] + t[2]);
            if (it->first <= std::max<int>(jt->first, v)) {
                x[0] = std::max<int>(it->first, u);
                s[it->second] = x[0];
                ++it;
            } else {
                x[1] = std::max<int>(jt->first, v);
                s[jt->second] = x[1];
                ++jt;
            }
        }
        while (it != q[0].end()) {
            x[0] = std::max<int>(it->first, std::max(x[1] + t[1], x[0] + t[3]));
            s[it->second] = x[0];
            ++it;
        }
        while (jt != q[1].end()) {
            x[1] = std::max<int>(jt->first, std::max(x[1] + t[0], x[0] + t[2]));
            s[jt->second] = x[1];
            ++jt;
        }
    }

    for (const unsigned x : s)
        print_time(x);

    return 0;
}
