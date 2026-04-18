#include <array>
#include <iostream>
#include <vector>

void match(const std::array<std::vector<unsigned>, 2>& targets, size_t t, size_t u, std::array<std::vector<unsigned>, 2>& matches)
{
    for (size_t v = targets[t][u]; matches[t][u] == 0 && matches[t^1][v] == 0; v = targets[t][u]) {
        matches[t][u] = v;
        matches[t^1][v] = u;

        const size_t w = targets[t^1][v];
        if (w != 0 && targets[t][w] != 0)
            u = w;
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t k;
    std::cin >> k;

    std::array<std::vector<unsigned>, 2> targets, sources, matches;
    for (size_t t = 0; t < 2; ++t) {
        targets[t].resize(1 + k);
        sources[t].resize(1 + k);
        matches[t].resize(1 + k);
    }

    for (size_t t = 0; t < 2; ++t) {
        for (size_t i = 1; i <= k; ++i) {
            unsigned x;
            std::cin >> x;

            targets[t][i] = x;
            if (x != 0)
                sources[t^1][x] = i;
        }
    }

    for (size_t t = 0; t < 2; ++t) {
        for (size_t i = 1; i <= k; ++i) {
            if (sources[t][i] == 0 && targets[t][i] != 0)
                match(targets, t, i, matches);
        }
    }
    for (size_t t = 0; t < 2; ++t) {
        for (size_t i = 1; i <= k; ++i) {
            if (targets[t][i] != 0 && matches[t][i] == 0)
                match(targets, t, i, matches);
        }
    }

    std::vector<unsigned> isolated[2];
    for (size_t t = 0; t < 2; ++t) {
        for (size_t i = 1; i <= k; ++i) {
            if (matches[t][i] == 0)
                isolated[t].push_back(i);
        }
    }
    for (const size_t i : isolated[0]) {
        matches[0][i] = isolated[1].back();
        isolated[1].pop_back();
    }

    for (size_t i = 1; i <= k; ++i)
        std::cout << matches[0][i] << ' ';

    return 0;
}
