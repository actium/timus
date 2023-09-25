#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct Directory {
    std::string name;

    Directory() = default;

    explicit Directory(const std::string& name)
        : name(name)
    {}

    std::vector<size_t> subdirectories;
};

std::vector<std::string> split(const std::string& path)
{
    const size_t n = path.length();

    std::vector<std::string> s(1);
    for (size_t i = 0; i < n; ++i) {
        if (path[i] == '\\')
            s.emplace_back();
        else
            s.back().push_back(path[i]);
    }

    if (s.back().empty())
        s.pop_back();

    return s;
}

std::vector<Directory> index(const std::vector<std::string>& p)
{
    std::vector<Directory> dirs(1);

    std::map<std::pair<size_t, std::string>, size_t> index;

    const auto get = [&](size_t p, const std::string& x) {
        const std::pair<size_t, std::string> k = { p, x };

        const auto it = index.find(k);
        if (it != index.end())
            return it->second;

        index.emplace(k, dirs.size());
        dirs.emplace_back(x);
        return dirs.size() - 1;
    };

    for (const std::string& q : p) {
        size_t r = 0;
        for (const std::string& d : split(q)) {
            const size_t x = get(r, d);
            dirs[r].subdirectories.push_back(x);
            r = x;
        }
    }

    return dirs;
}

void print(const std::vector<Directory>& dirs, size_t x, unsigned d)
{
    std::vector<size_t> s = dirs[x].subdirectories;
    std::sort(s.begin(), s.end(), [&](size_t i, size_t j) {
        return dirs[i].name < dirs[j].name;
    });
    s.erase(std::unique(s.begin(), s.end()), s.end());

    for (const size_t x : s) {
        std::cout << std::string(d, ' ') << dirs[x].name << '\n';
        print(dirs, x, d + 1);
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    std::vector<std::string> p(n);
    for (size_t i = 0; i < n; ++i)
        std::cin >> p[i];

    print(index(p), 0, 0);

    return 0;
}
