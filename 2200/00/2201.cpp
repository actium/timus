#include <iostream>
#include <map>
#include <set>
#include <string>

#include <cassert>
#include <cmath>

int compare(unsigned a, unsigned x, unsigned b, unsigned y)
{
    if (a == b)
        return x - y;

    const auto lhs = x * logl(a), rhs = y * logl(b);
    if (fabsl(lhs - rhs) < 1e-6)
        return 0;

    return lhs > rhs ? 1 : -1;
}

std::string extract_username(const std::string& s, size_t x)
{
    const size_t p1 = s.find('<', x);
    assert(p1 != std::string::npos);

    const size_t p2 = s.find('>', p1);
    assert(p2 != std::string::npos);

    return s.substr(p1 + 1, p2 - (p1 + 1));
}

std::pair<unsigned, unsigned> parse_message(const std::string& message)
{
    unsigned counts[2] = {};
    for (size_t i = 1; i < message.size(); i += 2)
        ++counts[message[i] == 'f'];

    return std::make_pair(counts[0], counts[1]);
}

struct User {
    unsigned gl = 0;
    unsigned hf = 0;

    unsigned gl_base;
    unsigned hf_bsae;
};

std::map<std::string, User*> user_database;

User* get_user(const std::string& username)
{
    auto it = user_database.find(username);
    if (it == user_database.end())
        it = user_database.emplace(username, new User()).first;

    return it->second;
}

int compare(unsigned a, unsigned b, const User* lhs, const User* rhs)
{
    const auto ca = std::min(lhs->gl, rhs->gl);
    const auto cb = std::min(lhs->hf, rhs->hf);

    const std::pair<unsigned, unsigned> lc = { lhs->gl - ca, rhs->hf - cb };
    const std::pair<unsigned, unsigned> rc = { rhs->gl - ca, lhs->hf - cb };

    if (lc.first == 0 && lc.second == 0)
        return -(rc.first != 0 || rc.second != 0);

    if (rc.first == 0 && rc.second == 0)
        return lc.first != 0 || lc.second != 0;

    assert(lc.first == 0 || lc.second == 0);
    assert(rc.first == 0 || rc.second == 0);

    if (lc.first == 0) {
        assert(rc.second == 0);
        return compare(b, lc.second, a, rc.first);
    } else {
        assert(rc.first == 0);
        return compare(a, lc.first, b, rc.second);
    }
    assert(false);
    return 0;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n;
    std::cin >> n;

    unsigned m, a, b;
    std::cin >> m >> a >> b;

    std::set<User*> online_users;

    User* const admin = get_user("admin");
    online_users.insert(admin);

    unsigned gl_total = 0;
    unsigned hf_total = 0;

    const auto update_user = [&](User* const user) {
        user->gl += gl_total - user->gl_base;
        user->gl_base = gl_total;

        user->hf += hf_total - user->hf_bsae;
        user->hf_bsae = hf_total;
    };

    for (size_t i = 0; i < n; ++i) {
        std::string timestamp, username, command;
        std::cin >> timestamp >> username >> command;

        assert(username.size() > 1 && username.back() == ':');
        username.pop_back();

        assert(command.length() >= 2 && command[0] == '/');
        if (command[1] == 'j') {
            User* const user = get_user(username);
            if (online_users.insert(user).second) {
                user->gl_base = gl_total;
                user->hf_bsae = hf_total;
                std::cout << "Successful" << '\n';
            } else {
                std::cout << "Failed: " << username << " is already on the server" << '\n';
            }
            continue;
        }
        if (command[1] == 'q') {
            User* const user = get_user(username);
            user->gl += gl_total - user->gl_base;
            user->hf += hf_total - user->hf_bsae;
            online_users.erase(user);
            std::cout << "Successful" << '\n';
            continue;
        }
        if (command[1] == 'o') {
            std::cout << "There are " << online_users.size() << " players on the server" << '\n';
            continue;
        }
        if (command[1] == 'c') {
            if (username != "admin") {
                std::cout << "Failed: you have no such rights" << '\n';
                continue;
            }

            update_user(admin);

            if (const size_t x = command.find('-', 5); x == std::string::npos) {
                const auto player = extract_username(command, 2);

                User* const user = get_user(player);
                if (online_users.find(user) != online_users.end()) {
                    update_user(user);

                    const auto d = compare(a, b, admin, user);
                    if (d == 0)
                        std::cout << player << " is good" << '\n';
                    else
                        std::cout << player << " is a " << (d > 0 ? "loser" : "lucky guy") << '\n';
                } else {
                    std::cout << "Failed: " << player << " is not on the server" << '\n';
                }
            } else {
                const std::string players[2] = { extract_username(command, 2), extract_username(command, x) };

                User* users[2] = {};
                for (size_t i = 0; i < 2; ++i) {
                    users[i] = get_user(players[i]);
                    if (online_users.find(users[i]) == online_users.end()) {
                        std::cout << "Failed: " << players[i] << " is not on the server" << '\n';
                        users[i] = nullptr;
                        break;
                    }
                    update_user(users[i]);
                }

                if (users[0] != nullptr && users[1] != nullptr) {
                    const auto d = compare(a, b, users[0], users[1]);
                    if (d == 0)
                        std::cout << "Their luck is equal" << '\n';
                    else
                        std::cout << players[1] << " is a " << (d > 0 ? "loser" : "lucky guy") << '\n';
                }
            }
            continue;
        }

        std::string message;
        std::cin >> message;

        const auto cs = parse_message(message);

        if (command[1] == 's') {
            User* const author = get_user(username);

            gl_total += cs.first;
            hf_total += cs.second;

            author->gl_base += cs.first;
            author->hf_bsae += cs.second;

            std::cout << username << ": " << message << '\n';
            continue;
        }
        if (command[1] == 'w') {
            const auto recipient = extract_username(command, 2);
            assert(recipient != username);

            User* user = get_user(recipient);
            if (online_users.find(user) != online_users.end()) {
                user->gl += cs.first;
                user->hf += cs.second;
            }
            std::cout << username << " (to " << recipient << "): " << message << '\n';
            continue;
        }

        assert(false);
    }

    return 0;
}
