#include <iostream>
#include <vector>

void solve(unsigned h, std::vector<std::pair<unsigned, unsigned>>& s)
{
    const size_t n = s.size();

    std::vector<int> sequence;
    if (s[0].first == s[0].second) {
        for (int i = 0; i < n && s[i].first == s[i].second; ++i) {
            if (s[i].first != s[0].first && h - s[i].first != s[0].first)
                break;

            sequence.push_back(s[i].first == s[0].first ? i + 1 : -(i + 1));
        }
    } else {
        std::vector<std::vector<int>> options(1 + h);
        unsigned min = h, max = 0;
        for (size_t i = 0; i < n; ++i) {
            if (s[i].first + s[0].second != s[0].first + s[i].second) {
                std::cout << '0' << '\n';
                return;
            }

            options[s[i].first].push_back(i + 1);

            min = std::min(min, std::min(s[i].first, h - s[i].second));
            max = std::max(max, std::max(s[i].first, h - s[i].second));
        }

        const int d = s[0].second - s[0].first;

        for (unsigned i = 0, x = d < 0 ? max : min; i < n; ++i, x += d) {
            if (!options[x].empty()) {
                sequence.push_back(options[x].back());
                options[x].pop_back();
                continue;
            }

            const unsigned y = h - (x + d);
            if (!options[y].empty()) {
                sequence.push_back(-options[y].back());
                options[y].pop_back();
                continue;
            }

            break;
        }
    }

    if (sequence.size() != n) {
        std::cout << '0' << '\n';
    } else {
        for (const int x : sequence)
            std::cout << x << ' ';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned h;
    std::cin >> h;

    size_t n;
    std::cin >> n;

    std::vector<std::pair<unsigned, unsigned>> s(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> s[i].first >> s[i].second;

    solve(h, s);

    return 0;
}
