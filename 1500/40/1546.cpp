#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::string_view select_number(const std::string& s, size_t x)
{
    const size_t p = x;

    while (x < s.size() && isdigit(s[x]))
        ++x;

    return std::string_view(s.data() + p, x - p);
}

std::string_view remove_leading_zeroes(std::string_view s)
{
    while (s.size() > 1 && s[0] == '0')
        s.remove_prefix(1);

    return s;
}

bool compare_strings(const std::string& lhs, const std::string& rhs)
{
    int d = 0;

    size_t i = 0, j = 0;
    while (i < lhs.size() && j < rhs.size()) {
        if (isdigit(lhs[i]) != isdigit(rhs[j]))
            return isdigit(lhs[i]);

        if (isalpha(lhs[i]) && lhs[i] != rhs[j])
            return lhs[i] < rhs[j];

        if (isdigit(lhs[i])) {
            const std::string_view s = select_number(lhs, i), t = select_number(rhs, j);

            const std::string_view u = remove_leading_zeroes(s), v = remove_leading_zeroes(t);
            if (u.length() != v.length())
                return u.length() < v.length();

            if (u != v)
                return u < v;

            if (d == 0)
                d = static_cast<int>(t.length() - s.length());

            i += s.length();
            j += t.length();
        } else {
            ++i;
            ++j;
        }
    }

    return i == lhs.size() && (j < rhs.size() || d < 0);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> s;
    for (std::string buffer; std::cin >> buffer; s.push_back(buffer));

    std::sort(s.begin(), s.end(), compare_strings);

    for (const auto& x : s)
        std::cout << x << '\n';

    return 0;
}
