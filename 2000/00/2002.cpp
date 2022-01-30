#include <iostream>
#include <unordered_map>
#include <string>

int main()
{
    unsigned n;
    std::cin >> n;

    std::unordered_map<std::string, std::pair<std::string, bool>> r;
    while (n-- > 0) {
        std::string c;
        std::cin >> c;

        if (c == "register") {
            std::string user, password;
            std::cin >> user >> password;

            if (!r.emplace(user, std::make_pair(password, false)).second) {
                std::cout << "fail: user already exists" << '\n';
                continue;
            }
            std::cout << "success: new user added" << '\n';
        }
        if (c == "login") {
            std::string user, password;
            std::cin >> user >> password;

            const auto it = r.find(user);
            if (it == r.end()) {
                std::cout << "fail: no such user" << '\n';
                continue;
            }
            if (it->second.first != password) {
                std::cout << "fail: incorrect password" << '\n';
                continue;
            }
            if (it->second.second) {
                std::cout << "fail: already logged in" << '\n';
                continue;
            }
            it->second.second = true;
            std::cout << "success: user logged in" << '\n';
        }
        if (c == "logout") {
            std::string user;
            std::cin >> user;

            const auto it = r.find(user);
            if (it == r.end()) {
                std::cout << "fail: no such user" << '\n';
                continue;
            }
            if (!it->second.second) {
                std::cout << "fail: already logged out" << '\n';
                continue;
            }
            it->second.second = false;
            std::cout << "success: user logged out" << '\n';
        }
    }

    return 0;
}
