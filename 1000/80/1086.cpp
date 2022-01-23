#include <iostream>
#include <vector>

void solve(const std::vector<unsigned>& a)
{
    constexpr unsigned N = 163845;

    std::vector<bool> c(N);
    for (unsigned i = 2; i * i < N; ++i) {
        if (c[i])
            continue;

        for (unsigned j = i * i; j < N; j += i)
            c[j] = true;
    }

    std::vector<unsigned> p;
    p.reserve(15000);
    for (unsigned i = 2; i < N; ++i) {
        if (!c[i])
            p.push_back(i);
    }

    for (const unsigned x : a)
        std::cout << p[x-1] << '\n';
}

int main()
{
    size_t k;
    std::cin >> k;

    std::vector<unsigned> a(k);
    for (size_t i = 0; i < k; ++i)
        std::cin >> a[i];

    solve(a);

    return 0;
}
