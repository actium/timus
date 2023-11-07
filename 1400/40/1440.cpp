#include <iostream>
#include <string>
#include <vector>

constexpr std::string_view day_names[7] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday",
};

unsigned index(const std::string& wd)
{
    size_t i = 0;
    while (wd != day_names[i])
        ++i;

    return i;
}

unsigned count(const std::string& m, unsigned d)
{
    constexpr std::string_view t[4] = {
        "September",
        "October",
        "November",
        "December",
    };

    size_t i = 0;
    while (m != t[i])
        ++i;

    constexpr unsigned q[4] = { 0, 30, 61, 91 };
    return d + q[i] - 2;
}

void solve(unsigned d, unsigned k, unsigned a, unsigned b)
{
    unsigned c[7] = {};
    for (unsigned i = 0; i < k; ++i)
        ++c[(d + i) % 7];

    unsigned dp[201] = { ~0u };
    for (size_t i = 0; i < 7; ++i) {
        if (c[i] == 0)
            continue;

        for (unsigned j = b; j >= c[i]; --j) {
            if (dp[j] == 0 && dp[j - c[i]] != 0)
                dp[j] = 1 + i;
        }
    }

    size_t i = a;
    while (i <= b && dp[i] == 0)
        ++i;

    if (i > b) {
        std::cout << "Impossible" << '\n';
        return;
    }

    std::vector<unsigned> s;
    while (i != 0) {
        s.push_back(dp[i]);
        i -= c[dp[i]-1];
    }

    std::cout << s.size() << '\n';
    for (const unsigned x : s)
        std::cout << day_names[x-1] << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string wd;
    std::cin >> wd;

    std::string m;
    std::cin >> m;

    unsigned d;
    std::cin >> d;

    unsigned a, b;
    std::cin >> a >> b;

    solve(index(wd) + 1, count(m, d), a, b);

    return 0;
}
