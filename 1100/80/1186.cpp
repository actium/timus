#include <iostream>
#include <map>
#include <string>
#include <vector>

using formula_t = std::map<std::string, unsigned>;

void scale(formula_t& f, unsigned x)
{
    if (x < 2)
        return;

    for (std::pair<const std::string, unsigned>& e : f)
        e.second *= x;
}

void merge(const formula_t& s, formula_t& t)
{
    for (const std::pair<const std::string, unsigned>& e : s)
        t[e.first] += e.second;
}

size_t parse_number(const std::string_view& s, unsigned& x)
{
    size_t p = 0;
    while (p < s.length() && isdigit(s[p])) {
        x *= 10;
        x += s[p++] - '0';
    }
    return p;
}

size_t parse_sequence(const std::string_view& s, char t, formula_t& f)
{
    const size_t n = s.length();

    size_t p = 0;
    while (p < n && s[p] != t) {
        if (s[p] == '(') {
            formula_t subsequence;
            p += parse_sequence(s.substr(++p), ')', subsequence);

            unsigned x = 0;
            p += parse_number(s.substr(p), x);
            scale(subsequence, x);

            merge(subsequence, f);
        } else {
            std::string element;
            element.push_back(s[p++]);
            if (islower(s[p]))
                element.push_back(s[p++]);

            unsigned x = 0;
            p += parse_number(s.substr(p), x);
            f[element] += std::max<unsigned>(x, 1);
        }
    }
    return p + 1;
}

size_t parse_formula(const std::string_view& s, char t, formula_t& f)
{
    size_t p = 0;

    unsigned x = 0;
    p += parse_number(s, x);
    p += parse_sequence(s.substr(p), t, f);
    scale(f, x);

    return p;
}

formula_t parse(const std::string_view& s)
{
    const size_t n = s.length();

    std::vector<formula_t> fs;
    for (size_t p = 0; p < n; ) {
        fs.emplace_back();
        p += parse_formula(s.substr(p), '+', fs.back());
    }

    formula_t f;
    for (const formula_t& p : fs)
        merge(p, f);

    return f;
}

void solve(const std::string& p, const std::vector<std::string>& q)
{
    const formula_t f = parse(p);

    for (const std::string& s : q)
        std::cout << p << (parse(s) == f ? "==" : "!=") << s << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string p;
    std::cin >> p;

    size_t n;
    std::cin >> n;

    std::vector<std::string> q(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> q[i];

    solve(p, q);

    return 0;
}
