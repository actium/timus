#include <iostream>
#include <vector>

constexpr unsigned oo = ~0u;

unsigned compute_sg(const std::vector<unsigned>& chain, size_t b, size_t e, std::vector<std::vector<unsigned>>& sg);

unsigned compute_xor(const std::vector<unsigned>& chain, size_t b, size_t e, unsigned v, std::vector<std::vector<unsigned>>& sg)
{
    unsigned x = 0;
    for (size_t p = b; p < e; ) {
        while (p < e && chain[p] <= v)
            ++p;

        const size_t q = p;

        while (p < e && chain[p] > v)
            ++p;

        x ^= compute_sg(chain, q, p, sg);
    }
    return x;
}

unsigned compute_sg(const std::vector<unsigned>& chain, size_t b, size_t e, std::vector<std::vector<unsigned>>& sg)
{
    if (e - b <= 1)
        return e - b;

    if (sg[b][e-1] == oo) {
        bool r[101] = {}, s[101] = {};
        for (size_t i = b; i < e; ++i) {
            if (r[chain[i]])
                continue;

            const unsigned x = compute_xor(chain, b, e, chain[i], sg);
            if (x <= 100)
                s[x] = true;

            r[chain[i]] = true;
        }

        unsigned x = 0;
        while (x <= 100 && s[x])
            ++x;

        sg[b][e-1] = x;
    }
    return sg[b][e-1];
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t k;
    std::cin >> k;

    std::vector<std::vector<unsigned>> chains(k);
    for (size_t i = 0; i < k; ++i) {
        size_t m;
        std::cin >> m;

        chains[i].resize(m);
        for (size_t j = 0; j < m; ++j)
            std::cin >> chains[i][j];
    }

    std::vector<std::vector<std::vector<unsigned>>> sg(k);
    for (size_t i = 0; i < k; ++i) {
        const size_t m = chains[i].size();
        sg[i].resize(m, std::vector<unsigned>(m, ~0u));
        compute_sg(chains[i], 0, m, sg[i]);
    }

    unsigned x = 0;
    for (size_t i = 0; i < k; ++i) {
        const size_t m = chains[i].size();
        x ^= compute_sg(chains[i], 0, m, sg[i]);
    }

    if (x != 0) {
        std::pair<size_t, size_t> t = {};
        while (true) {
            const auto& chain = chains[t.first];

            const size_t m = chain.size();
            x ^= compute_sg(chain, 0, m, sg[t.first]);

            for (t.second = 0; t.second < m; ++t.second) {
                if (compute_xor(chain, 0, m, chain[t.second], sg[t.first]) == x)
                    break;
            }
            if (t.second < m)
                break;

            x ^= compute_sg(chain, 0, m, sg[t.first++]);
        }

        std::cout << 'G' << '\n';
        std::cout << 1+t.first << ' ' << 1+t.second << '\n';
    } else {
        std::cout << 'S' << '\n';
    }

    return 0;
}
