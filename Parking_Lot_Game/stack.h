#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T>
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary
};
template <class T>
Stack<T>::Stack()
{

}
template <class T>
Stack<T>::~Stack()
{

}
template <class T>
bool Stack<T>::empty() const
{
    return std::vector<T>::empty();

}
template <class T>
size_t Stack<T>::size() const
{
    return std::vector<T>::size();

}
template <class T>
void Stack<T>::push(const T& item)
{
    std::vector<T>::push_back(item);

}
template <class T>
void Stack<T>::pop()
{
    if(std::vector<T>::empty())
        throw std::underflow_error("The stack is empty");
    std::vector<T>::pop_back();

}
template <class T>
const T& Stack<T>::top() const
{
    if(std::vector<T>::empty())
        throw std::underflow_error("The stack is empty");
    return std::vector<T>::back();

}




#endif