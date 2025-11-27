#ifndef DOUBLELIST_DOUBLELIST_H
#define DOUBLELIST_DOUBLELIST_H

#include "../lib_list/list.h"


template <class T>
class DoubleList : public List<T> {
public:
    DoubleList();
    DoubleList(const DoubleList<T>&);

    class Iterator : public List<T>::Iterator {
    public:
        Iterator() : List<T>::Iterator() {}
        Iterator(Node<T>* node) : List<T>::Iterator(node) {}

        Iterator& operator--() {  // --it
            _current = _current->_prev;
            return *this;
        }
        Iterator operator--(int) {  // it--
            Iterator tmp(_current);
            _current = _current->_prev;
            return tmp;
        }
        Iterator& operator-=(const int count) {
            for (int i = count; i != 0; i--)
                _current = _current->_prev;
            return *this;
        }
        Iterator& operator=(const Iterator& other) {
            this->_current = other._current;
            return *this;
        }
    };

    Iterator begin() {
        return _head;
    }

    Iterator end() {
        if (_tail == nullptr) return nullptr;
        return _tail->_next;
    }

    void push_front(const T&) noexcept;
    void push_back(const T&) noexcept;
    void insert(size_t, const T&);
    void insert(Node<T>*, const T&);

    void pop_front();
    void erase(size_t);
    void erase(Node<T>*);
};

template <class T>
DoubleList<T>::DoubleList() : List<T>() {}

template <class T>
DoubleList<T>::DoubleList(const DoubleList& other) : List<T>() {
    _count = 0;
    Node<T>* cur = other._head;
    while (cur != nullptr) {
        push_back(cur->_value);
        cur = cur->_next;
    }
}

template <class T>
void DoubleList<T>::push_front(const T& value) noexcept {
    Node<T>* old_head = _head;
    List<T>::push_front(value);
    if (old_head != nullptr)
        old_head->_prev = _head;
}

template <class T>
void DoubleList<T>::push_back(const T& value) noexcept {
    Node<T>* old_tail = _tail;
    List<T>::push_back(value);
    _tail->_prev = old_tail;
}

template <class T>
void DoubleList<T>::insert(Node<T>* node, const T& value) {
    if (node == nullptr)
        throw std::invalid_argument("Null node");
    if (is_empty())
        throw std::logic_error("List is empty");
    Node<T>* new_node = new Node<T>(value, node->_next, node);
    node->_next = new_node;
    new_node->_next->_prev = new_node;
    if (node == _tail)
        _tail = new_node;
    _count++;
}

template <class T>
void DoubleList<T>::insert(size_t pos, const T& value) {
    if (pos == 0) {
        push_front(value);
        return;
    }
    if (pos == _count) {
        push_back(value);
        return;
    }
    Node<T>* cur = _head;
    size_t cur_pos = 0;
    while (cur != nullptr) {
        if (cur_pos == pos - 1)
            break;
        cur_pos++;
        cur = cur->_next;
    }
    if (cur == nullptr)
        throw std::invalid_argument("Wrong position");
    insert(cur, value);
}

template <class T>
void DoubleList<T>::pop_front() {
    List<T>::pop_front();
    if (_head != nullptr)
        _head->_prev = nullptr;
}

template <class T>
void DoubleList<T>::erase(Node<T>* node) {
    List<T>::erase(node);
    node->_next->_prev = node;
}

template <class T>
void DoubleList<T>::erase(size_t pos) {
    if (pos == 0) {
        pop_front();
        return;
    }
    if (pos == _count - 1) {
        pop_back();
        return;
    }
    Node<T>* cur = _head;
    size_t cur_pos = 0;
    while (cur != nullptr) {
        if (cur_pos == pos - 1)
            break;
        cur_pos++;
        cur = cur->_next;
    }
    if (cur == nullptr)
        throw std::invalid_argument("Wrong position");
    erase(cur);
}


#endif // !DOUBLELIST_DOUBLELIST_H