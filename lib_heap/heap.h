#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include "../lib_TVector/tvector.h"

template <class T>
class Heap {
    TVector<T> _data;

public:
    Heap();

    void push(const T&);
    T pop();

    inline int get_left(const int i) const noexcept { return 2 * i + 1; }
    inline int get_right(const int i) const noexcept { return 2 * i + 2; }
};

template <class T>
Heap<T>::Heap() : _data() {}

template <class T>
void Heap<T>::push(const T& value) {
    _data.push_back(value);

    int i_value = _data.size() - 1, i_parent = (i_value -1) / 2;

    while (i_parent >= 0 && _data[i_value] < _data[i_parent]) {
        std::swap(_data[i_value], _data[i_parent]);
        i_value = i_parent;
        i_parent = i_parent = (i_value - 1) / 2;
    }
}

template <class T>
T Heap<T>::pop() {
    int i_value = 0, left, right,
        size = _data.size(), smallest = i_value;
    T deleted = _data.front();
    _data[0] = _data[_data.size() - 1];
    _data.pop_back();

    while (true) {
        left = get_left(i_value);
        right = get_right(i_value);

        if (left < size && _data[left] < _data[smallest])
            smallest = left;
        if (right < size && _data[right] < _data[smallest])
            smallest = right;

        if (smallest == i_value) 
            break;

        std::swap(_data[i_value], _data[smallest]);
        i_value = smallest;
    }

    return deleted;
}

#endif // !HEAP_HEAP_H
