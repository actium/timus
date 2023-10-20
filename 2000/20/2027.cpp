#include <iostream>
#include <string>
#include <utility>
#include <vector>

void execute(const std::vector<std::string>& t, unsigned n)
{
    const size_t h = t.size(), w = t[0].length();

    std::pair<int, int> p = { 0, 0 };
    std::pair<int, int> d = { 1, 0 };
    int r[28] = {};
    for (unsigned i = 0, j = 0; i < 1000000; ++i) {
        switch (t[p.second][p.first]) {
            case '^':
                d = { 0, -1 };
                break;

            case '>':
                d = { 1, 0 };
                break;

            case 'v':
                d = { 0, 1 };
                break;

            case '<':
                d = { -1, 0 };
                break;

            case '.':
                break;

            case '?':
                if (j++ < n)
                    std::cin >> r[27];

                r[26] = r[27];
                break;

            case '!':
                std::cout << std::exchange(r[26], 0) << '\n';
                break;

            case '+':
                if (++r[26] > 100000) {
                    std::cout << "OVERFLOW ERROR";
                    return;
                }
                break;

            case '-':
                if (--r[26] < -100000) {
                    std::cout << "OVERFLOW ERROR";
                    return;
                }
                break;

            case '@':
                std::swap(d.first, d.second);
                r[26] == 0 ? d.second = -d.second : d.first = -d.first;
                break;

            case '#':
                return;

            default:
                std::swap(r[t[p.second][p.first] - 'A'], r[26]);
                break;
        }

        p.first += d.first;
        p.second += d.second;

        if (p.first >= w || p.second >= h) {
            std::cout << "RUNTIME ERROR";
            return;
        }
    }

    std::cout << "TIME LIMIT EXCEEDED";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t h, w;
    std::cin >> h >> w;

    std::vector<std::string> t(h);
    for (size_t i = 0; i < h; ++i)
        std::cin >> t[i];

    unsigned n;
    std::cin >> n;

    execute(t, n);

    return 0;
}
