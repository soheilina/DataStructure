#include "../Node/node.hpp"
#include "../Vertex/Vertex.hpp"

template<class T>
class Stack{
public:
    Stack();
    ~Stack() = default;
public:
    void push(T element);
    T pop();
    void drop();
    bool isEmpty();
private:
    std::vector<T> m_stack;
};