#include <iostream>
#include <string>
#include <vector>

struct Expression {
    virtual bool evaluate(const bool registers[26]) const = 0;
    virtual ~Expression() = default;
};

class Literal : public Expression {
public:
    explicit Literal(bool value)
        : value_(value)
    {}

    bool evaluate(const bool registers[26]) const override
    {
        return value_;
    }

private:
    bool value_;

}; // class Literal

class Reference : public Expression {
public:
    explicit Reference(char index)
        : index_(index)
    {}

    bool evaluate(const bool registers[26]) const override
    {
        return registers[index_ - 'A'];
    }

private:
    const char index_;

}; // class Reference

class Not : public Expression {
public:
    explicit Not(const Expression* operand)
        : operand_(operand)
    {}

    bool evaluate(const bool registers[26]) const override
    {
        return !operand_->evaluate(registers);
    }

private:
    const Expression* operand_;

}; // class Not

class And : public Expression {
public:
    And(const Expression* lhs, const Expression* rhs)
        : lhs_(lhs)
        , rhs_(rhs)
    {}

    bool evaluate(const bool registers[26]) const override
    {
        return lhs_->evaluate(registers) && rhs_->evaluate(registers);
    }

private:
    const Expression* lhs_;
    const Expression* rhs_;

}; // class And

class Or : public Expression {
public:
    Or(const Expression* lhs, const Expression* rhs)
        : lhs_(lhs)
        , rhs_(rhs)
    {}

    bool evaluate(const bool registers[26]) const override
    {
        return lhs_->evaluate(registers) || rhs_->evaluate(registers);
    }

private:
    const Expression* lhs_;
    const Expression* rhs_;

}; // class Or

std::vector<std::string> tokenize(const std::string& s)
{
    const size_t n = s.length();

    std::vector<std::string> tokens;

    std::vector<size_t> p;
    for (size_t i = 0; i < n; ++i) {
        if (s[i] == '(') {
            p.push_back(i);
            continue;
        }
        if (s[i] == ')') {
            const size_t x = p.back() + 1;
            p.pop_back();
            if (p.empty())
                tokens.push_back(s.substr(x, i - x));
            continue;
        }
        if (!p.empty() || s[i] == ' ')
            continue;

        if (s[i] == 'O' && i + 1 < n && s[i+1] == 'R') {
            tokens.push_back("OR");
            i += 1;
            continue;
        }
        if (s[i] == 'A' && i + 2 < n && s[i+1] == 'N') {
            tokens.push_back("AN");
            i += 2;
            continue;
        }
        if (s[i] == 'N' && i + 2 < n && s[i+1] == 'O') {
            tokens.push_back("NO");
            i += 2;
            continue;
        }
        if (s[i] == 'T' && i + 3 < n && s[i+1] == 'R') {
            tokens.push_back("TR");
            i += 3;
            continue;
        }
        if (s[i] == 'F' && i + 4 < n && s[i+1] == 'A') {
            tokens.push_back("FA");
            i += 4;
            continue;
        }

        tokens.push_back(s.substr(i, 1));
    }

    return tokens;
}

const Expression* parse(const std::vector<std::string>& tokens, size_t lb, size_t ub)
{
    for (size_t i = lb; i < ub; ++i) {
        if (tokens[i] == "OR")
            return new Or(parse(tokens, lb, i), parse(tokens, i + 1, ub));
    }
    for (size_t i = lb; i < ub; ++i) {
        if (tokens[i] == "AN")
            return new And(parse(tokens, lb, i), parse(tokens, i + 1, ub));
    }

    if (tokens[lb] == "NO")
        return new Not(parse(tokens, lb + 1, ub));
    if (tokens[lb] == "TR")
        return new Literal(true);
    if (tokens[lb] == "FA")
        return new Literal(false);
    if (tokens[lb].length() == 1)
        return new Reference(tokens[lb][0]);

    const std::vector<std::string> subtokens = tokenize(tokens[lb]);
    return parse(subtokens, 0, subtokens.size());
}

void solve(const std::string& t, const std::vector<std::string>& map)
{
    const int n = map.size() / 2;

    const Expression* program = nullptr;
    {
        const std::vector<std::string> tokens = tokenize(t);
        program = parse(tokens, 0, tokens.size());
    }

    bool registers[26] = {};
    for (int x = n, y = n, dx = 1, dy = 0; x >= 0 && x <= 2 * n && y >= 0 && y <= 2 * n; x += dx, y += dy) {
        std::cout << x - n << ' ' << y - n << '\n';

        if (map[x][y] == ' ')
            continue;

        if (map[x][y] == '+') {
            const bool v = program->evaluate(registers);
            if (v) {
                const int ndx = dy;
                dy = -dx;
                dx = ndx;
            } else {
                const int ndy = dx;
                dx = -dy;
                dy = ndy;
            }
        } else {
            const size_t r = map[x][y] - 'A';
            registers[r] = !registers[r];
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string t;
    std::getline(std::cin, t);

    size_t n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::string> map(n + 1 + n, std::string(n + 1 + n, ' '));
    for (size_t i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;

        map[n + x][n + y] = '+';
    }
    for (size_t i = 0; i < k; ++i) {
        int x, y;
        std::cin >> x >> y;

        std::cin >> map[n + x][n + y];
    }

    solve(t, map);

    return 0;
}
