#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <cassert>

struct Recipe {
    std::string name;
    std::vector<std::pair<std::string, double>> components;
    bool resolved;

    void simplify()
    {
        std::sort(components.begin(), components.end());

        for (size_t i = 1; i < components.size(); ++i) {
            if (components[i].first == components[i-1].first) {
                components[i-1].second += components[i].second;
                components.erase(components.begin() + i--);
            }
        }

        const auto it = std::lower_bound(components.begin(), components.end(), std::make_pair(name, 0.0));
        if (it != components.end() && it->first == name) {
            const double x = 1 / (1 - it->second);
            assert(x > 0);
            for (auto& c : components)
                c.second *= x;

            components.erase(it);
        }
    }
};

std::map<std::string, double> ingredients;

void resolve(Recipe& recipe, std::map<std::string, Recipe>& recipes)
{
    if (recipe.resolved)
        return;

    auto& components = recipe.components;
    for (size_t i = 0; i < components.size(); ++i) {
        if (components[i].first == recipe.name)
            continue;

        const auto it = recipes.find(components[i].first);
        if (it == recipes.end()) {
            ingredients.emplace(components[i].first, 0);
            continue;
        }

        if (it->first < recipe.name)
            continue;

        resolve(it->second, recipes);

        for (const auto& c : it->second.components)
            components.emplace_back(c.first, c.second * components[i].second);

        components[i--] = components.back();
        components.pop_back();
    }

    recipe.simplify();

    recipe.resolved = true;
}

void solve(std::map<std::string, Recipe>& recipes)
{
    for (auto& e : recipes)
        resolve(e.second, recipes);

    for (auto& e : recipes) {
        auto& components = e.second.components;
        for (size_t i = 0; i < components.size(); ++i) {
            const auto it = recipes.find(components[i].first);
            if (it == recipes.end())
                continue;

            for (const auto& c : it->second.components) {
                assert(c.first != e.first);
                components.emplace_back(c.first, c.second * components[i].second);
            }

            components[i--] = components.back();
            components.pop_back();
        }

        for (auto& x : ingredients)
            x.second = 0;

        for (const auto& c : components)
            ingredients[c.first] += c.second;

        std::cout << e.first << " :";
        for (const auto& x : ingredients)
            std::cout << ' ' << x.first << ' ' << std::fixed << 100 * x.second;
        std::cout << '\n';
    }
}

std::vector<std::pair<std::string, double>> parse_recipe(const std::string& recipe)
{
    std::vector<std::pair<std::string, double>> components;
    for (std::istringstream input(recipe); input; ) {
        components.emplace_back();
        input >> components.back().first >> components.back().second;

        if (components.back().second > 0)
            components.back().second /= 100;
        else
            components.pop_back();
    }
    return components;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::map<std::string, Recipe> recipes;
    for (std::string buffer; std::getline(std::cin, buffer); ) {
        const size_t x = buffer.find(':');
        assert(x != 0);

        const auto recipe_name = buffer.substr(0, x-1);
        recipes[recipe_name] = { recipe_name, parse_recipe(buffer.substr(x + 1)), false };
    }

    solve(recipes);

    return 0;
}
