#ifndef MATHVECTOR_MATHVECTOR_H
#define MATHVECTOR_MATHVECTOR_H

#include "../lib_TVector/tvector.h"
#include <initializer_list>

template <class T>
class MathVector : public TVector<T> {
    int _start_index;

public:
    MathVector();
    MathVector(const int, const int start_index = 0);
    MathVector(std::initializer_list<T>, const int start_index = 0);
    MathVector(const MathVector&);

    T& operator[](const int&);

};

template <class T>
MathVector<T>::MathVector() : TVector(), _start_index(0) {}

template <class T>
MathVector<T>::MathVector(const int size, const int start_index) : TVector(size) {
    if (start_index < 0 || start_index >= size)
        throw std::invalid_argument("Invalid start_index");
    _start_index = start_index;
}

template <class T>
MathVector<T>::MathVector(std::initializer_list<T> vector, const int start_index) : TVector(vector) {
    if (start_index < 0 || start_index >= vector.size())
        throw std::invalid_argument("Invalid start_index");
    _start_index = start_index;
}

template <class T>
MathVector<T>::MathVector(const MathVector<T>& other_vector) {
    _size = other_vector._size;
    _capacity = other_vector._capacity;
    _start_index = other_vector._start_index;

    for (int i = 0; i < _capacity; i++) {
        if (i < other_vector._size) {
            _vec[i] = other_vector._vec[i];
            _status[i] = other_vector._status[i];
        }
        else _status[i] = Status::Empty;
    }
}

template <class T>
T& MathVector<T>::operator[](const int&) {
    T coord;
    return coord;
}

#endif // !MATHVECTOR_MATHVECTOR_H
