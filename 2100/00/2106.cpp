#include <iostream>
#include <string>
#include <vector>

struct Definition {
    std::string name;
    std::vector<std::string> field_types;
};

template <size_t k>
unsigned deserialize_integer(std::string_view& s)
{
    unsigned value = 0;
    for (size_t i = 0; i < k; ++i) {
        value <<= 4;
        value += (s[i] <= '9' ? s[i] - '0' : s[i] - 'A' + 10);
    }
    s.remove_prefix(k);
    return value;
}

std::string deserialize_string(std::string_view& s)
{
    const unsigned length = deserialize_integer<8>(s);

    std::string t;
    t.reserve(length);
    for (unsigned i = 0; i < length; ++i)
        t.push_back(deserialize_integer<2>(s));

    return t;
}

void deserialize_structure(const Definition& x, std::string_view& s, unsigned indentation, const std::vector<Definition>& defs)
{
    std::cout << std::string(indentation, ' ') << x.name << '\n';

    for (const std::string& field_type : x.field_types) {
        if (field_type == "int") {
            std::cout << std::string(indentation + 1, ' ') << "int " << deserialize_integer<8>(s) << '\n';
            continue;
        }
        if (field_type == "string") {
            std::cout << std::string(indentation + 1, ' ') << "string " << deserialize_string(s) << '\n';
            continue;
        }

        size_t i = 0;
        while (defs[i].name != field_type)
            ++i;

        deserialize_structure(defs[i], s, indentation + 1, defs);
    }
}

void solve(const std::vector<Definition>& defs, std::string_view s)
{
    while (!s.empty()) {
        const unsigned index = deserialize_integer<8>(s) - 1;
        deserialize_structure(defs[index], s, 0, defs);
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, l;
    std::cin >> n >> l >> std::ws;

    std::vector<Definition> defs(n);
    for (size_t i = 0, k = -1; i < l; ++i) {
        std::string s;
        std::getline(std::cin, s);

        if (s.compare(0, 6, "struct") == 0) {
            defs[++k].name = s.substr(7);
        } else {
            defs[k].field_types.push_back(s.substr(1));
        }
    }

    std::string s;
    std::getline(std::cin, s);

    solve(defs, s);

    return 0;
}
