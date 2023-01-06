#include <iostream>
#include <map>
#include <set>
#include <vector>

using integer = unsigned long long;

struct Person {
    unsigned id;
    unsigned location;
    integer fortune;
};

struct Location {
    unsigned id;
    std::string name;
    integer rating;
};

bool operator <(const Location& lhs, const Location& rhs)
{
    return std::make_pair(lhs.rating, lhs.id) < std::make_pair(rhs.rating, rhs.id);
}

template <typename T>
class Index {
public:
    unsigned size() const
    {
        return items_.size();
    }

    T& operator [](const std::string& name)
    {
        const auto it = ids_.find(name);
        if (it != ids_.end())
            return items_[it->second];

        const unsigned id = items_.size();
        ids_.emplace(name, id);
        items_.emplace_back();
        items_[id].id = id;
        return items_[id];
    }

    T& operator [](unsigned id)
    {
        return items_[id];
    }

private:
    std::vector<T> items_;
    std::map<std::string, unsigned> ids_;

}; // class Index

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned n;
    std::cin >> n;

    Index<Person> persons;
    Index<Location> locations;

    for (unsigned i = 0; i < n; ++i) {
        std::string name, location;
        std::cin >> name >> location;

        Person& person = persons[name];
        person.location = locations[location].id;
        std::cin >> person.fortune;

        locations[person.location].name = location;
        locations[person.location].rating += person.fortune;
    }

    std::set<Location> heap;
    for (unsigned i = 0; i < locations.size(); ++i)
        heap.insert(locations[i]);

    std::map<unsigned, unsigned> tops;

    const auto update_tops = [&](unsigned dt) {
        if (heap.empty() || dt == 0)
            return;

        if (heap.size() == 1) {
            tops[heap.begin()->id] += dt;
        } else {
            const auto it = heap.rbegin(), jt = std::next(it);
            if (it->rating != jt->rating)
                tops[it->id] += dt;
        }
    };

    unsigned m, k;
    std::cin >> m >> k;

    unsigned t = 0;
    for (unsigned i = 0; i < k; ++i) {
        unsigned date;
        std::cin >> date;

        update_tops(date - t);

        std::string person, destination;
        std::cin >> person >> destination;

        Person& p = persons[person];
        Location& d = locations[destination];
        if (d.name.empty())
            d.name = destination;

        Location& s = locations[p.location];
        {
            heap.erase(s);
            s.rating -= p.fortune;
            heap.insert(s);
        }

        p.location = d.id;
        {
            heap.erase(d);
            d.rating += p.fortune;
            heap.insert(d);
        }

        t = date;
    }

    update_tops(m - t);

    std::map<std::string, unsigned> results;
    for (const auto& e : tops)
        results.emplace(locations[e.first].name, e.second);

    for (const auto& e : results)
        std::cout << e.first << ' ' << e.second << '\n';

    return 0;
}
