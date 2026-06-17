#include <iostream>
#include <string>
#include <vector>

constexpr std::string_view colors = "BGRWY";

unsigned clear(std::vector<std::string>& b, size_t i, size_t j, char x)
{
    unsigned k = 0;
    if (i < b.size() && j < b[i].size() && b[i][j] == x) {
        b[i][j] = ' ';
        k = 1;

        k += clear(b, i-1, j, x);
        k += clear(b, i, j+1, x);
        k += clear(b, i+1, j, x);
        k += clear(b, i, j-1, x);
    }
    return k;
}

struct Component {
    size_t i;
    size_t j;
    char c;
    unsigned k = 0;
};

unsigned simulate(std::vector<std::string> b, char x)
{
    unsigned score = 0;
    while (!b.empty()) {
        const auto h = b.size(), w = b[0].size();

        Component p, q;
        {
            std::vector<std::string> r = b;
            for (size_t i = 0; i < h; ++i) {
                for (size_t j = 0; j < w; ++j) {
                    if (r[i][j] == ' ')
                        continue;

                    const auto c = r[i][j];
                    const auto k = clear(r, i, j, c);

                    if (c != x && k > p.k)
                        p = { i, j, c, k };

                    if (c == x && k > q.k)
                        q = { i, j, c, k };
                }
            }
        }

        if (p.k < 2 && q.k < 2)
            break;

        const auto remove = [&](const Component& c) {
            score += c.k * (c.k - 1);

            clear(b, c.i, c.j, c.c);

            for (size_t i = 1; i < h; ++i) {
                for (size_t j = 0; j < w; ++j) {
                    if (b[i][j] == ' ')
                        continue;

                    for (size_t k = i; k > 0 && b[k-1][j] == ' '; --k)
                        std::swap(b[k-1][j], b[k][j]);
                }
            }

            while (!b.empty() && b.back().find_first_not_of(' ') == std::string::npos)
                b.pop_back();

            if (b.empty())
                return;

            for (size_t j = b[0].size()-1; j > 0; --j) {
                unsigned k = 0;
                for (size_t i = 0; i < b.size() && b[i][j-1] == ' '; ++i)
                    ++k;

                if (k == b.size()) {
                    for (size_t i = 0; i < b.size(); ++i)
                        b[i].erase(b[i].begin() + j-1);
                }
            }
        };

        remove(p.k > 1 ? p : q);
    }
    return score;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::string> b(n);
    for (size_t i = n-1; ~i != 0; --i)
        std::cin >> b[i];

    for (const auto c : colors) {
        for (const auto& s : b) {
            if (s.find(c) != std::string::npos) {
                const auto score = simulate(b, c);
                std::cout << c << ':' << ' ' << score << '\n';
                break;
            }
        }
    }

    return 0;
}
