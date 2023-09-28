#include <iostream>

using integer = unsigned long long;

constexpr integer t[] = {
    0,
    10,
    100,
    6700,
    448900,
    37018840,
    3052783504,
    266095289560,
    23194144960900,
    2082728967969200,
    187019610394369600,
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    unsigned n;
    std::cin >> n;

    std::cout << t[n/2] << '\n';

    return 0;
}
