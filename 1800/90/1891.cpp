#include <iostream>
#include <map>
#include <string>
#include <vector>

using symbol_table_t = std::map<std::string, char>;

std::string output;

void dump_variable_info(const std::pair<std::string, char>& v)
{
    output += v.first;
    output += " : ";

    switch (v.second) {
        case 'I': output += "int"; break;
        case 'R': output += "real"; break;
        case 'S': output += "string"; break;
    }

    output += '\n';
}

char parse_type_name(const std::string& s, size_t& i)
{
    if (s.compare(i, 3, "int") == 0) {
        i += 3;
        return 'I';
    }
    if (s.compare(i, 4, "real") == 0) {
        i += 4;
        return 'R';
    }
    if (s.compare(i, 6, "string") == 0) {
        i += 6;
        return 'S';
    }
    if (s.compare(i, 4, "auto") == 0) {
        i += 4;
        return 'A';
    }
    return ' ';
}

void parse_function_declaration(const std::string& s, symbol_table_t& functions)
{
    const size_t lp = s.find('('), rp = s.rfind(':');

    std::string signature = s.substr(0, lp);
    signature.push_back(' ');
    for (size_t i = lp + 1; i < rp; ++i) {
        const char t = parse_type_name(s, i);
        if (t != ' ')
            signature.push_back(t);
    }

    for (size_t i = rp + 1; i < s.length(); ++i) {
        const char t = parse_type_name(s, i);
        if (t != ' ') {
            functions.emplace(signature, t);
            break;
        }
    }
}

std::string parse_variable_initialization(const std::string& s, const symbol_table_t& functions, symbol_table_t& variables)
{
    const auto locate_alpha = [&](size_t& i) {
        while (!isalpha(s[i]))
            ++i;
    };

    std::pair<std::string, char> variable;
    {
        size_t i = 0;
        do {
            variable.second = parse_type_name(s, i);
            ++i;
        } while (variable.second == ' ');

        locate_alpha(i);

        while (isalpha(s[i])) {
            variable.first.push_back(s[i]);
            ++i;
        }

        if (variables.find(variable.first) != variables.end())
            return "Double declaration";

        locate_alpha(i);

        std::string signature;
        while (s[i] != '(') {
            signature.push_back(s[i]);
            ++i;
        }
        signature.push_back(' ');

        std::string buffer;
        for (++i; i < s.length(); ++i) {
            if (isalpha(s[i])) {
                buffer.push_back(s[i]);
                continue;
            }

            if (buffer.empty())
                continue;

            const auto it = variables.find(buffer);
            if (it == variables.end())
                return "Unknown variable";

            signature.push_back(it->second);
            buffer.clear();
        }

        const auto it = functions.find(signature);
        if (it == functions.end())
            return "No such function";

        if (variable.second == 'A') {
            variable.second = it->second;
            dump_variable_info(variable);
        }

        if (variable.second != it->second)
            return "Invalid initialization";
    }
    variables.insert(variable);
    return "";
}

std::string solve(const std::vector<std::string>& f, const std::vector<std::string>& v)
{
    symbol_table_t functions;
    for (const std::string& s : f)
        parse_function_declaration(s, functions);

    symbol_table_t variables;
    for (size_t i = 0; i < v.size(); ++i) {
        const std::string error = parse_variable_initialization(v[i], functions, variables);
        if (!error.empty())
            return "Error on line " + std::to_string(i + 1) + ": " + error;
    }
    return output;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n >> std::ws;

    std::vector<std::string> f(n);
    for (size_t i = 0; i < n; ++i)
        std::getline(std::cin, f[i]);

    size_t m;
    std::cin >> m >> std::ws;

    std::vector<std::string> v(m);
    for (size_t i = 0; i < m; ++i)
        std::getline(std::cin, v[i]);

    std::cout << solve(f, v) << '\n';

    return 0;
}
