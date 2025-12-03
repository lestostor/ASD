#ifndef LISTSTACK_LISTSTACK_H
#define LISTSTACK_LISTSTACK_H

#include "../lib_list/list.h"
#include <stdexcept>

template <class T>
class ListStack {
    List<T> _data;
    int _size = -1;
public:
    ListStack(const int size = -1);
    ListStack(const ListStack<T>&);

    void push(T);
    void pop();
    T top() const;
    inline bool is_empty() const noexcept {
        return _data.is_empty();
    }
    inline bool is_full() const noexcept {
        return _data.get_size() == _size;
    }
    void clear() noexcept;
};

template <class T>
ListStack<T>::ListStack(const int size) : _data(), _size(size) {}

template <class T>
ListStack<T>::ListStack(const ListStack<T>& other) : _data(other._data), _size(other._size) {}

template <class T>
void ListStack<T>::push(T element) {
    if (is_full())
        throw std::logic_error("Stack is full");
    _data.push_front(element);
}

template <class T>
void ListStack<T>::pop() {
    if (_data.is_empty())
        throw std::logic_error("Stack is empty");
    _data.pop_front();
}

template <class T>
T ListStack<T>::top() const {
    if (_data.is_empty())
        throw std::logic_error("Stack is empty");
    return _data.head()->_value;
}

template <class T>
void ListStack<T>::clear() noexcept {
    while (!_data.is_empty())
        _data.pop_front();
}

#endif // !LISTSTACK_LISTSTACK_H
