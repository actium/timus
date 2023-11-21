#include <iostream>
#include <string>

constexpr char t[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void solve(unsigned a, unsigned b, unsigned k)
{
    std::string m;
    {
        unsigned x = a / b;
        do {
            m.push_back(t[x % k]);
            x /= k;
        } while (x != 0);
    }

    std::cout << std::string(m.rbegin(), m.rend());

    a %= b;

    if (a != 0) {
        std::string f = ".";

        unsigned x[1 + 9999 * 36] = {};
        for (unsigned i = 1; a != 0; a %= b, ++i) {
            a *= k;

            if (x[a] != 0) {
                f.insert(f.begin() + x[a], '(');
                f.push_back(')');
                break;
            }
            x[a] = i;

            f.push_back(t[a / b]);
        }

        std::cout << f;
    }

    std::cout << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned a, b, k;
    while (std::cin >> a >> b, b != 0) {
        std::cin >> k;

        solve(a, b, k);
    }

    return 0;
}
