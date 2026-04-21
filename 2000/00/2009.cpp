#include <iostream>
#include <set>
#include <vector>

struct Student {
    std::vector<Student*> s;
    std::set<Student*> p;

    Student* next = nullptr;

    unsigned q;
    unsigned t;
};

struct Group {
    unsigned t;
    std::vector<Student*> s;
};

struct Queue {
    Student* head = nullptr;
    Student* tail = nullptr;

    unsigned k = 0;
    unsigned t = 0;
};

void solve(std::vector<Student>& students, const std::vector<Group>& groups)
{
    Queue queues[2];

    const auto dequeue = [&](unsigned t) {
        for (size_t i = 0; i < 2; ++i) {
            while (queues[i].t < t && queues[i].head != nullptr) {
                const auto s = queues[i].head;
                queues[i].head = s->next;
                --queues[i].k;
                s->t = ++queues[i].t;

                for (const auto t : s->s)
                    t->p.erase(s);
            }
        }
    };

    for (const auto& group : groups) {
        dequeue(group.t);

        for (const auto student : group.s) {
            std::pair<unsigned, Student*> v[2] = {
                std::make_pair(queues[0].k, queues[0].tail),
                std::make_pair(queues[1].k, queues[1].tail),
            };
            for (const auto t : student->p) {
                unsigned d = 1;
                for (auto x = queues[t->q].head; x != t; x = x->next)
                    ++d;

                if (d < v[t->q].first) {
                    v[t->q].first = d;
                    v[t->q].second = t;
                }
            }

            student->q = (v[1].first <= v[0].first);
            if (queues[student->q].head == nullptr) {
                queues[student->q].t = group.t;
                queues[student->q].head = student;
                queues[student->q].tail = student;
            } else {
                student->next = v[student->q].second->next;
                v[student->q].second->next = student;
                if (queues[student->q].tail == v[student->q].second)
                    queues[student->q].tail = student;
            }
            ++queues[student->q].k;

            for (const auto t : student->s)
                t->p.insert(student);
        }
    }

    dequeue(~0u);

    for (const auto& s : students)
        std::cout << s.t << ' ' << (s.q == 0 ? "left" : "right") << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    size_t n, m;
    std::cin >> n >> m;

    std::vector<Student> students(n);
    for (size_t i = 0; i < n; ++i)
        for (unsigned x; std::cin >> x && x != 0; students[x-1].s.push_back(&students[i]));

    std::vector<Group> groups(m);
    for (size_t i = 0; i < m; ++i) {
        std::cin >> groups[i].t;

        size_t k;
        std::cin >> k;

        for (size_t j = 0; j < k; ++j) {
            unsigned x;
            std::cin >> x;

            groups[i].s.push_back(&students[x-1]);
        }
    }

    solve(students, groups);

    return 0;
}
