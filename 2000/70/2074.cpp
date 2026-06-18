#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::map<std::string, std::string> topics;                  // topic id -> FQTN
    std::map<unsigned, std::vector<std::string>> problem_tags;  // problem id -> topic ids
    {
        std::vector<std::string> prefixes;
        for (std::string buffer, last_id; std::getline(std::cin, buffer); ) {
            if (const size_t x = buffer.rfind('.'); x != std::string::npos) {
                last_id = buffer.substr(0, x);
                while (!prefixes.empty() && last_id.find(prefixes.back()) != 0)
                    prefixes.pop_back();

                auto topic = buffer.substr(buffer.find_first_not_of(' ', x+1));
                if (!prefixes.empty())
                    topic = topics[prefixes.back()] + '.' + topic;

                topics[last_id] = topic;
                prefixes.push_back(last_id);
            } else {
                buffer.push_back(' ');
                for (size_t s = 0, t; s < buffer.size(); s = t + 1) {
                    t = buffer.find(' ', s);

                    const auto problem_id = buffer.substr(s, t - s);
                    problem_tags[std::stoi(problem_id)].push_back(last_id);
                }
            }
        }
    }

    std::map<std::vector<std::string>, std::vector<unsigned>> tagged_problems;
    for (const auto& e : problem_tags)
        tagged_problems[e.second].push_back(e.first);

    std::vector<std::pair<std::vector<unsigned>, std::vector<std::string>>> result_set;
    for (auto& e : tagged_problems) {
        std::sort(e.second.begin(), e.second.end());
        result_set.emplace_back(e.second, e.first);
    }

    std::sort(result_set.begin(), result_set.end());

    for (const auto& [problem_ids, topic_ids] : result_set) {
        for (const unsigned problem_id : problem_ids) {
            if (problem_id != problem_ids[0])
                std::cout << ", ";
            std::cout << problem_id;
        }
        std::cout << " : ";

        std::vector<std::string> tags;
        for (const auto& topic_id : topic_ids)
            tags.push_back(topics[topic_id]);

        std::sort(tags.begin(), tags.end());

        for (const auto& tag : tags) {
            if (tag != tags[0])
                std::cout << ", ";
            std::cout << tag;
        }
        std::cout << '\n';
    }

    return 0;
}
