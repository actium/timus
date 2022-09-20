#include <iostream>
#include <string>

bool check(const std::string& s)
{
    for (size_t k = s.length(); k > 0; ) {
        if (k >= 6 && s.compare(k-6, 6, "output") == 0)
            k -= 6;
        else if (k >= 5 && s.compare(k-5, 5, "input") == 0)
            k -= 5;
        else if (k >= 5 && s.compare(k-5, 5, "puton") == 0)
            k -= 5;
        else if (k >= 3 && s.compare(k-3, 3, "one") == 0)
            k -= 3;
        else if (k >= 3 && s.compare(k-3, 3, "out") == 0)
            k -= 3;
        else if (k >= 2 && s.compare(k-2, 2, "in") == 0)
            k -= 2;
        else
            return false;
    }
    return true;
}

void test_case()
{
    std::string s;
    std::cin >> s;

    std::cout << (check(s) ? "YES" : "NO") << '\n';
}

int main()
{
    unsigned n;
    std::cin >> n;

    for (unsigned i = 0; i < n; ++i)
        test_case();

    return 0;
}
