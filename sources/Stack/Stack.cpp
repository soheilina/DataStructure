#include "Stack.hpp"

template <class T>
Stack<T>::Stack()
    : m_stack(){};

template <class T> void Stack<T>::push(T element) { m_stack.push_back(element); }

template <class T> T Stack<T>::pop() {
    T top = m_stack[m_stack.size() - 1];
    m_stack.erase(--m_stack.end());
    return top;
}

template <class T> void Stack<T>::drop() { m_stack.erase(--m_stack.end()); }

template <class T> bool Stack<T>::isEmpty() { return (m_stack.size() == 0); }

template class Stack<std::string>;
template class Stack<int>;
template class Stack<Node*>;