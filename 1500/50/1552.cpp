#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>

constexpr unsigned oo = ~0u;

unsigned distance(unsigned s, unsigned t)
{
    return s < t ? t - s : s - t;
}

struct State {
    unsigned source;
    unsigned cursor;
    std::array<char, 4> variables;
    unsigned length;
};

State make_state(unsigned source, unsigned cursor, std::array<char, 4> variables, unsigned length)
{
    return { source, cursor, variables, length };
}

std::string generate_program(const std::vector<State>& states, unsigned x)
{
    std::string program;
    for (unsigned s = states[x].source; s != oo; x = s, s = states[x].source) {
        const unsigned c = states[x].cursor;

        program.push_back('.');

        const unsigned dv = distance(states[s].variables[c], states[x].variables[c]);
        program.append(dv, "-+"[states[s].variables[c] < states[x].variables[c]]);

        const unsigned dc = distance(c, states[s].cursor);
        program.append(dc, "<>"[states[s].cursor < c]);
    }
    return std::string(program.rbegin(), program.rend());
}

std::string solve(const std::string& s)
{
    const size_t n = s.size();

    std::vector<State> states;
    for (unsigned c = 0; c < 4; ++c)
        states.push_back(make_state(oo, c, {}, 0));

    size_t x = 0;
    for (size_t i = 0; i < n; ++i) {
        using Key = std::pair<unsigned, std::array<char, 4>>;
        std::map<Key, std::pair<unsigned, unsigned>> candidates;

        for ( ; x < states.size(); ++x) {
            const auto& source = states[x];

            for (unsigned c = 0; c < 4; ++c) {
                const unsigned dc = distance(source.cursor, c);
                const unsigned dv = distance(source.variables[c], s[i]);

                std::array<char, 4> variables = source.variables;
                variables[c] = s[i];

                const auto key = std::make_pair(c, variables);
                const auto it = candidates.emplace(key, std::make_pair(oo, x)).first;
                if (source.length + dc + dv < it->second.first) {
                    it->second.first = source.length + dc + dv;
                    it->second.second = static_cast<unsigned>(x);
                }
            }
        }

        for (const auto& e : candidates)
            states.push_back(make_state(e.second.second, e.first.first, e.first.second, e.second.first));
    }

    size_t t = x;
    while (++x < states.size()) {
        if (states[x].length < states[t].length)
            t = x;
    }
    return generate_program(states, t);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s;
    std::cin >> s;

    std::cout << solve(s) << '\n';

    return 0;
}
