#ifndef LISTQUEUE_LISTQUEUE_H
#define LISTQUEUE_LISTQUEUE_H

#include "../lib_list/list.h"
#include <stdexcept>

template <class T>
class ListQueue {
    List<T> _data;
    int _size = -1;

public:
    ListQueue(const int size = -1);
    ListQueue(const ListQueue<T>&);

    void push(int);
    void pop();
    inline T tail() const {
        return _data.tail()->_value;
    }
    inline T head() const {
        return _data.head()->_value;
    }
    inline bool is_empty() const noexcept {
        return _data.is_empty();
    }
    inline bool is_full() const noexcept {
        return _data.get_size() == _size;
    }
    void clear() noexcept;
};

template <class T>
ListQueue<T>::ListQueue(const int size) : _data(), _size(size) {}

template <class T>
ListQueue<T>::ListQueue(const ListQueue<T>& other) : _data(other._data), _size(other._size) {}

template <class T>
void ListQueue<T>::push(int value) {
    if (is_full())
        throw std::logic_error("Queue is full");
    _data.push_back(value);
}

template <class T>
void ListQueue<T>::pop() {
    if (is_empty())
        throw std::logic_error("Queue is empty");
    _data.pop_front();
}

template <class T>
void ListQueue<T>::clear() noexcept {
    while (!_data.is_empty())
        _data.pop_front();
}

#endif // !LISTQUEUE_LISTQUEUE_H
