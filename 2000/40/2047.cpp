#include <iostream>

constexpr unsigned S = 1586335, K = 100000;

unsigned c[1 + S];
unsigned a[1 + K];

void prepare()
{
    for (unsigned i = 2; i <= S; ++i) {
        for (unsigned j = i; j <= S; j += i)
            ++c[j];
    }

    for (unsigned s = S, i = K; i > 0; s -= a[i], --i)
        a[i] = c[s] + 1;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    prepare();

    unsigned n;
    std::cin >> n;

    for (unsigned i = 1; i <= n; ++i)
        std::cout << a[i] << ' ';

    return 0;
}
