#include <iostream>
#include <vector>

void traverse(const std::vector<unsigned>& a, size_t& index, unsigned lb, unsigned ub)
{
    if (~index == 0)
        return;

    const unsigned key = a[index];
    if (key <= lb || key >= ub)
        return;

    if (index-- > 0) {
        traverse(a, index, key, ub);
        traverse(a, index, lb, key);
    }

    std::cout << key << '\n';
}

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<unsigned> a(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> a[i];

    size_t index = n - 1;
    traverse(a, index, 0, ~0u);

    return 0;
}
