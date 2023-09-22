#include <iostream>
#include <string>
#include <vector>

std::vector<unsigned> parse(const std::string& s)
{
    const size_t n = s.length();

    std::vector<unsigned> v;
    for (size_t i = 0, j = 0; i < n; ++i) {
        if (!isalpha(s[i])) {
            const size_t d = i - j;
            if (d != 0)
                v.push_back(d);

            j = i + 1;
        }
    }
    return v;
}

unsigned solve(const std::string& t)
{
    const std::vector<unsigned> w = parse(t);

    const size_t k = w.size();

    std::vector<unsigned> dp1(1 + k), dp2(1 + k);
    for (size_t i = 1; i <= k; ++i) {
        dp1[i] = dp2[i-1] + w[i-1];
        dp2[i] = std::max(dp1[i-1], dp2[i-1]);
    }

    return std::max(dp1[k], dp2[k]);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string t;
    t.reserve(512 * 1024);
    for (std::string s; std::getline(std::cin, s); ) {
        t.append(s);
        t.push_back(' ');
    }

    std::cout << solve(t) << '\n';

    return 0;
}
