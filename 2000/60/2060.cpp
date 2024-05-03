#include <iostream>
#include <string>
#include <vector>

using integer = unsigned long long;

std::vector<unsigned> manacher(std::string_view s)
{
    std::string t = " ";
    for (const char c : s) {
        t.push_back(c);
        t.push_back(' ');
    }

    const size_t n = t.length();

    std::vector<unsigned> v(n);
    for (size_t i = 0, j = 0; i < n; ) {
        while (i >= j && i + j < n && t[i-j] == t[i+j])
            ++j;

        v[i] = j;

        size_t k = 1;
        while (i >= k && i + k < n && k + v[i-k] < j) {
            v[i+k] = v[i-k];
            ++k;
        }

        i += k;
        j -= k;
    }
    return v;
}

integer solve(const std::string& s)
{
    const size_t n = s.length();

    const std::vector<unsigned> v = manacher(s);

    std::vector<int> p(n+1), q(n+1);
    for (size_t i = 0; i < n; ++i) {
        const unsigned re = v[2*i] / 2;
        ++p[i-re], --p[i];
        ++q[i], --q[i+re];

        const unsigned ro = v[2*i+1] / 2;
        ++p[i-ro+1], --p[i+1];
        ++q[i], --q[i+ro];
    }

    for (size_t i = 1; i < n; ++i) {
        p[i] += p[i-1];
        q[i] += q[i-1];
    }

    integer k = 0;
    for (size_t i = 1; i < n; ++i)
        k += 1ull * q[i-1] * p[i];

    return k;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    std::cout << solve(s) << '\n';

    return 0;
}
