#include <iostream>
#include <vector>

using integer = unsigned long long;

constexpr unsigned M = 1'000'000'007;

unsigned solve(integer n, integer k, unsigned q)
{
    if (n < q)
        return 0;

    std::vector<integer> digits;
    while (n != 0) {
        digits.push_back(n % k);
        n /= k;
    }

    integer s = 0;
    for (const auto d : digits)
        s += d;

    if (s >= q)
        return s == q;

    const auto r = static_cast<unsigned>(q - s);
    if (r % (k - 1) != 0)
        return 0;

    const unsigned t = r / static_cast<unsigned>(k - 1), m = digits.size();

    std::vector<std::vector<unsigned>> dp(1+t, std::vector<unsigned>(1+t));
    dp[0][0] = 1;
    for (size_t i = m-1; i != 0; --i) {
        std::vector<std::vector<unsigned>> ndp(1+t, std::vector<unsigned>(1+t));
        for (unsigned carry = 0; carry <= t; ++carry) {
            for (unsigned used = 0; used <= t; ++used) {
                if (dp[carry][used] == 0)
                    continue;

                const unsigned max_used = std::min<unsigned>(t - used, digits[i] + k * carry);
                for (unsigned x = 0; x <= max_used; ++x)
                    ndp[x][used+x] = (ndp[x][used+x] + dp[carry][used]) % M;
            }
        }

        std::swap(dp, ndp);
    }

    integer c = 0;
    for (unsigned carry = 0; carry <= t; ++carry)
        c += dp[carry][t];

    return c % M;
}

void test_case()
{
    integer n, k;
    std::cin >> n >> k;

    unsigned q;
    std::cin >> q;

    std::cout << solve(n, k, q) << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t t;
    std::cin >> t;

    while (t-- > 0)
        test_case();

    return 0;
}
