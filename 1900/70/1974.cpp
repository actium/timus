#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map<std::string, unsigned> t;

void initialize()
{
    const auto make_key = [&](unsigned i, const char* s) {
        std::string key;
        key.push_back(char('0' + i));
        key.append(s);
        return key;
    };

    for (unsigned i = 1, x = 0; i <= 8; ++i, x += 12) {
        t.emplace(make_key(i, "C-"), x + 0);
        t.emplace(make_key(i, "C"),  x + 1);
        t.emplace(make_key(i, "C+"), x + 2);
        t.emplace(make_key(i, "D-"), x + 2);
        t.emplace(make_key(i, "D"),  x + 3);
        t.emplace(make_key(i, "D+"), x + 4);
        t.emplace(make_key(i, "E-"), x + 4);
        t.emplace(make_key(i, "E"),  x + 5);
        t.emplace(make_key(i, "F-"), x + 5);
        t.emplace(make_key(i, "E+"), x + 6);
        t.emplace(make_key(i, "F"),  x + 6);
        t.emplace(make_key(i, "F+"), x + 7);
        t.emplace(make_key(i, "G-"), x + 7);
        t.emplace(make_key(i, "G"),  x + 8);
        t.emplace(make_key(i, "G+"), x + 9);
        t.emplace(make_key(i, "A-"), x + 9);
        t.emplace(make_key(i, "A"),  x + 10);
        t.emplace(make_key(i, "A+"), x + 11);
        t.emplace(make_key(i, "B-"), x + 11);
        t.emplace(make_key(i, "B"),  x + 12);
        t.emplace(make_key(i, "B+"), x + 13);
    }

    t.erase("1C-");
    t.erase("8B+");
}

struct Melody : std::vector<unsigned> {};

std::istream& operator >>(std::istream& input_stream, Melody& melody)
{
    size_t k;
    input_stream >> k;

    melody.resize(k);
    for (size_t i = 0; i < k; ++i) {
        std::string x;
        std::cin >> x;

        melody[i] = t[x];
    }

    return input_stream;
}

unsigned intersect(const Melody& u, int x, const Melody& v)
{
    const size_t n = u.size(), m = v.size();
    const size_t lb = std::max(x, 0), ub = std::min(m + x, n);

    unsigned k = 0;
    for (size_t i = lb; i < ub; ++i)
        k += (u[i] == v[i-x]);

    return k;
}

double compare(const Melody& t, const Melody& p)
{
    const size_t n = t.size(), m = p.size();

    unsigned k = 0;
    for (int x = 1 - m; x < static_cast<int>(n); ++x)
        k = std::max(k, intersect(t, x, p));

    return k / static_cast<double>(m);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    initialize();

    Melody text;
    std::cin >> text;

    size_t m;
    std::cin >> m;

    for (size_t i = 0; i < m; ++i) {
        Melody pattern;
        std::cin >> pattern;

        std::cout << std::fixed << compare(text, pattern) << '\n';
    }

    return 0;
}
