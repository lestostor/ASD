#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <stdexcept>

template <class T>
class Stack {
    T* _data;
    int _top = -1;
    int _size;

public:
    Stack();
    Stack(int);
    Stack(const Stack&);
    ~Stack();

    void push(int);
    void pop();
    T top() const;
    inline bool is_empty() const noexcept {
        return _top == -1;
    }
    inline bool is_full() const noexcept {
        return _top == _size - 1;
    }
    void clear() noexcept;
};

template <class T>
Stack<T>::Stack() {
    _size = 15;
    _data = new T[_size];
}

template <class T>
Stack<T>::Stack(int size) {
    if (size <= 0)
        throw std::invalid_argument("Size of stack must be > 0");
    _size = size;
    _data = new T[_size];
}

template <class T>
Stack<T>::Stack(const Stack& other) {
    _size = other._size;
    _top = other._top;
    _data = new T[_size];
    for (int i = 0; i < _size; i++)
        _data[i] = other._data[i];
}

template <class T>
void Stack<T>::push(int value) {
    if (is_full())
        throw std::logic_error("The stack is full");

    _data[++_top] = value;
}

template <class T>
void Stack<T>::pop() {
    if (is_empty())
        throw std::logic_error("The stack is empty");

    _top--;
}

template <class T>
T Stack<T>::top() const {
    if (is_empty())
        throw std::logic_error("The stack is empty");

    return _data[_top];
}

template <class T>
void Stack<T>::clear() noexcept {
    _top = -1;
}

template <class T>
Stack<T>::~Stack() {
    delete[] _data;
}

#endif // !STACK_STACK_H
