#include <iostream>

void test_case()
{
    char f, r;
    std::cin >> f >> r;

    constexpr unsigned t1[8] = { 2, 3, 4, 4, 4, 4, 3, 2 };
    if (f == 'a' || f == 'h') {
        std::cout << t1[r-'1'] << '\n';
        return;
    }
    if (r == '1' || r == '8') {
        std::cout << t1[f-'a'] << '\n';
        return;
    }

    constexpr unsigned t2[8] = { 3, 4, 6, 6, 6, 6, 4, 3 };
    if (f == 'b' || f == 'g') {
        std::cout << t2[r-'1'] << '\n';
        return;
    }
    if (r == '2' || r == '7') {
        std::cout << t2[f-'a'] << '\n';
        return;
    }

    std::cout << 8 << '\n';
}

int main()
{
    size_t t;
    std::cin >> t;

    while (t-- > 0)
        test_case();

    return 0;
}
