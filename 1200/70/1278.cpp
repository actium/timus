#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned k;
    std::cin >> k;

    --k;

    std::vector<unsigned> a;
    while (k != 0) {
        const auto b = 1ull << a.size();
        if (b <= k) {
            a.push_back(a.size());
            k -= b;
        } else {
            a.push_back(__builtin_ctz(k));
            k &= k - 1;
        }
    }

    for (auto it = a.rbegin(); it != a.rend(); ++it)
        std::cout << "CALL " << a.size() - *it << '\n';

    std::cout << "BELL&RET" << '\n';

    return 0;
}
