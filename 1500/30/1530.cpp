#include <iostream>
#include <string>

bool increment(std::string& v)
{
    size_t x = v.size() - 1;
    while (~x != 0 && ++v[x] == '2')
        v[x--] = '0';

    return ~x == 0;
}

void solve(std::string& p, std::string& q)
{
    const size_t n = p.length();

    if (increment(q))
        increment(p);

    size_t x = 0;
    while (x < n && (p[x] == '0' || q[x] == '0'))
        ++x;

    if (x < n) {
        while (~x != 0 && (p[x] == '1' || q[x] == '1'))
            --x;

        if (~x == 0 || q[x] == '1') {
            increment(p);
            q.assign(n, '0');
        } else {
            q[x] = '1';
            q.replace(x+1, n-1-x, n-1-x, '0');
        }
    }

    std::cout << p << '\n';
    std::cout << q << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::string p, q;
    std::cin >> p >> q;

    solve(p, q);

    return 0;
}
