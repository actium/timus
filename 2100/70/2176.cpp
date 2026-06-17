#include <bits/stdc++.h>

constexpr unsigned L = 64601292;

constexpr unsigned t[] = {
           1,        9,       10,       12,        94,       118,       120,      1002,
        1003,     2217,    22204,    22602,     26608,     27004,     27009,    531795,
      774202,   776424,   776467,  1604056,   1616464,   1660780,   1673176,   1673299,
     5021473,  5039860,  5039902,  5039904,   5042124,   5321298,   6384861,  16495194,

    16495195, 50218140, 63858541, 63951048, 133991280, 133991289, 133991290, 133991292,
};

std::bitset<L+1> lhs = 1;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    for (size_t i = 0; i < 32; ++i)
        lhs |= lhs << t[i];

    std::array<unsigned, 256> rhs = {};
    for (unsigned mask = 0; mask < 256; ++mask) {
        for (unsigned x = mask; x != 0; x &= x - 1)
            rhs[mask] += t[32 + __builtin_ctz(x)];
    }

    std::sort(rhs.begin(), rhs.end());

    const auto check = [&](unsigned x) {
        for (auto it = rhs.begin(); it != rhs.end() && *it <= x; ++it) {
            if (const unsigned r = x - *it; r <= L && lhs[r])
                return "YES";
        }
        return "NO";
    };

    size_t n;
    std::cin >> n;

    for (size_t i = 0; i < n; ++i) {
        unsigned x;
        std::cin >> x;

        std::cout << check(x) << '\n';
    }

    return 0;
}
