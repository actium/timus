#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using integer = unsigned long long;

std::unordered_map<integer, integer> cache;

integer phi(integer x, unsigned a, const std::vector<unsigned>& primes)
{
    if (a == 0)
        return x;

    if (x < primes[a-1])
        return 1;

    const integer key = (x << 6) | a;

    auto it = cache.find(key);
    if (it == cache.end())
        it = cache.emplace(key, phi(x, a-1, primes) - phi(x / primes[a-1], a-1, primes)).first;

    return it->second;
}

integer solve(unsigned a, unsigned b, unsigned k)
{
    const unsigned ub = k + 1;

    std::vector<unsigned> primes;
    {
        std::vector<bool> p(1+ub, true);
        for (unsigned i = 2; i <= ub; ++i) {
            if (!p[i])
                continue;

            primes.push_back(i);

            for (unsigned j = i * i; j <= ub; j += i)
                p[j] = false;
        }
    }

    const auto count_primes = [&](unsigned x) {
        return std::upper_bound(primes.begin(), primes.end(), x) - primes.begin();
    };

    const unsigned q = static_cast<unsigned>(primes.size());

    integer v = phi(a + b, q, primes) - phi(std::max(a, ub), q, primes);
    if (a < std::min(a + b, ub))
        v += count_primes(std::min(a + b, ub)) - count_primes(a);

    return v;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned a, b, k;
    std::cin >> a >> b >> k;

    std::cout << solve(a, b, k) << '\n';

    return 0;
}
