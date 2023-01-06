#include <array>
#include <vector>

#include <cstdio>

class Stack {
    static constexpr unsigned CHUNK_SIZE = 16;

    using Chunk = std::array<unsigned, CHUNK_SIZE>;

    static std::vector<Chunk> chunks_;

public:
    static void reserve(unsigned n)
    {
        chunks_.reserve(n / 4);
    }

    void push(unsigned v)
    {
        const unsigned x = size_ / CHUNK_SIZE;
        if (x == index_.size()) {
            index_.push_back(chunks_.size());
            chunks_.emplace_back();
        }

        chunks_[index_[x]][size_ % CHUNK_SIZE] = v;
        ++size_;
    }

    unsigned pop()
    {
        --size_;

        const unsigned x = size_ / CHUNK_SIZE;
        return chunks_[index_[x]][size_ % CHUNK_SIZE];
    }

private:
    std::vector<unsigned> index_;

    unsigned size_ = 0;

}; // class Stack

std::vector<Stack::Chunk> Stack::chunks_;

int main()
{
    unsigned n;
    scanf("%u\n", &n);

    Stack::reserve(n);

    Stack s[1000];
    for (size_t i = 0; i < n; ++i) {
        char c[5];
        scanf("%s ", c);

        if (c[1] == 'O') {
            unsigned x;
            scanf("%u\n", &x);

            printf("%u\n", s[x-1].pop());
        } else {
            unsigned x, y;
            scanf("%u %u\n", &x, &y);

            s[x-1].push(y);
        }
    }

    return 0;
}
