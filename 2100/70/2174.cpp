#include <iostream>
#include <queue>
#include <vector>

#include <cassert>

using graph_t = std::vector<std::vector<size_t>>;

struct Sieve {
    const unsigned upper_bound;

    std::vector<unsigned> smallest_prime_factors;
    std::vector<unsigned> primes;

    explicit Sieve(unsigned upper_bound)
        : upper_bound(upper_bound)
        , smallest_prime_factors(1 + upper_bound)
    {
        for (unsigned i = 2; i <= upper_bound; ++i) {
            if (smallest_prime_factors[i] == 0) {
                smallest_prime_factors[i] = i;
                primes.push_back(i);
            }

            for (const unsigned p : primes) {
                if (p > smallest_prime_factors[i] || i * p > upper_bound)
                    break;

                smallest_prime_factors[i * p] = p;
            }
        }
    }

    bool test_primality(unsigned n) const
    {
        if (n <= upper_bound)
            return n != 0 && smallest_prime_factors[n] == n;

        assert(upper_bound >= n / upper_bound && "number is too big");

        for (const unsigned p : primes) {
            if (p * p > n)
                break;

            if (n % p == 0)
                return false;
        }
        return n > 1;
    }
};

const Sieve soe(2000000);

void search(const graph_t& g, std::vector<unsigned>& times, std::vector<size_t>& parents, std::vector<size_t>& mates, size_t root)
{
    const size_t n = g.size();

    std::vector<unsigned> labels(n);

    std::vector<size_t> origins(n);
    for (size_t i = 0; i < n; ++i)
        origins[i] = i;

    static unsigned aux_time = 0;

    const auto lca = [&](size_t u, size_t v) {
        ++aux_time;

        while (u == 0 || times[u] != aux_time) {
            times[u] = aux_time;
            u = (mates[u] == 0 ? 0 : origins[parents[mates[u]]]);
            std::swap(u, v);
        }
        return u;
    };

    std::queue<size_t> q;

    const auto enqueue = [&](size_t u) {
        q.push(u);
        labels[u] = 1;
    };

    const auto blossom = [&](size_t u, size_t v, size_t x) {
        while (origins[u] != x) {
            parents[u] = v;
            v = mates[u];

            origins[u] = x;
            u = parents[v];

            origins[v] = x;
            if (labels[v] == 2)
                enqueue(v);
        }
    };

    const auto augment = [&](size_t u) {
        do {
            const size_t p = parents[u];
            const size_t v = mates[p];
            mates[u] = p;
            mates[p] = u;
            u = v;
        } while (u != 0);
    };

    enqueue(root);
    while (!q.empty()) {
        const size_t u = q.front();
        q.pop();

        for (const size_t v : g[u]) {
            if (labels[v] == 0) {
                parents[v] = u;
                if (mates[v] == 0)
                    return augment(v);

                enqueue(mates[v]);
                labels[v] = 2;
            }
            if (labels[v] == 1 && origins[u] != origins[v]) {
                const size_t x = lca(origins[u], origins[v]);
                blossom(v, u, x);
                blossom(u, v, x);
            }
        }
    }
}

void solve(const std::vector<unsigned>& c)
{
    const size_t n = c.size();

    graph_t g(1+n);
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (soe.test_primality(c[i] + c[j])) {
                g[1+i].push_back(1+j);
                g[1+j].push_back(1+i);
            }
        }
    }

    std::vector<size_t> mates(1+n);
    {
        std::vector<unsigned> times(1+n);
        std::vector<size_t> parents(1+n);

        for (size_t i = 1; i <= n; ++i) {
            if (mates[i] == 0)
                search(g, times, parents, mates, i);
        }
    }

    std::vector<std::pair<unsigned, unsigned>> s;
    for (size_t i = 1; i <= n; ++i) {
        if (mates[i] != 0) {
            s.emplace_back(i, mates[i]);
            mates[mates[i]] = 0;
        }
    }

    if (2 * s.size() < n) {
        std::cout << "NO" << '\n';
    } else {
        std::cout << "YES" << '\n';
        for (const auto& [u, v] : s)
            std::cout << c[u-1] << ' ' << c[v-1] << '\n';
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<unsigned> c(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> c[i];

    solve(c);

    return 0;
}
