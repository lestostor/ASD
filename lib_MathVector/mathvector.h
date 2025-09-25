#ifndef MATHVECTOR_MATHVECTOR_H
#define MATHVECTOR_MATHVECTOR_H

#include "../lib_TVector/tvector.h"
#include <initializer_list>

template <class T>
class MathVector : public TVector<T> {
protected:
    int _start_index;

public:
    MathVector();
    MathVector(const int, const int start_index = 0);
    MathVector(std::initializer_list<T>, const int start_index = 0);
    MathVector(const MathVector&);

    void clear() = delete;
    void push_back(const T&) = delete;
    void push_front(const T&) = delete;
    void insert(const T*, const T&) = delete;
    void pop_back() = delete;
    void pop_front() = delete;
    void erase(const T*) = delete;
    void emplace(const T&, const T&) = delete;
    void emplace(const T*, const T&) = delete;

    MathVector<T> operator+(const MathVector<T>);
    MathVector<T> operator-(const MathVector<T>);
    MathVector<T> operator*(const T&);
    MathVector<T> operator=(const MathVector<T>);
    T operator*(const MathVector<T>);

    T& operator[](const int);
    T& operator[](const int) const;

};

template <class T>
MathVector<T>::MathVector() : TVector<T>(), _start_index(0) {}

template <class T>
MathVector<T>::MathVector(const int size, const int start_index) : TVector<T>(size) {
    if (start_index < 0 || start_index >= size)
        throw std::invalid_argument("Invalid start_index");
    _start_index = start_index;
    this->shrink_to_fit();
}

template <class T>
MathVector<T>::MathVector(std::initializer_list<T> vector, const int start_index) : TVector<T>(vector) {
    if (start_index < 0 || start_index >= vector.size())
        throw std::invalid_argument("Invalid start_index");
    _start_index = start_index;
    this->shrink_to_fit();
}

template <class T>
MathVector<T>::MathVector(const MathVector<T>& other_vector) {
    _size = other_vector._size;
    _capacity = other_vector._size;
    _vec = new T[_size];
    _status = new Status[_size];
    _start_index = other_vector._start_index;

    for (int i = 0; i < _size; i++) {
        _vec[i] = other_vector._vec[i];
        _status[i] = other_vector._status[i];
    }
}

template <class T>
T& MathVector<T>::operator[](const int index) {
    return TVector<T>::operator[](index - _start_index);
}

template <class T>
T& MathVector<T>::operator[](const int index) const {
    return TVector<T>::operator[](index - _start_index);
}

template <class T>
MathVector<T> MathVector<T>::operator+(const MathVector<T> other_vector) {
    if (this->_size != other_vector._size)
        throw std::invalid_argument("Vectors have different sizes");

    MathVector<T> result(_size);
    for (int i = 0; i < _size; i++) {
        result[i] = this->_vec[i] + other_vector[i];
    }

    return result;
}

template <class T>
MathVector<T> MathVector<T>::operator-(const MathVector<T> other_vector) {
    if (this->_size != other_vector._size)
        throw std::invalid_argument("Vectors have different sizes");

    MathVector<T> result(_size);
    for (int i = 0; i < _size; i++) {
        result[i] = this->_vec[i] - other_vector[i];
    }

    return result;
}

template <class T>
MathVector<T> MathVector<T>::operator*(const T& number) {
    MathVector<T> result(_size);
    for (int i = 0; i < _size; i++)
        result[i] = _vec[i] * number;

    return result;
}

template <class T>
T MathVector<T>::operator*(const MathVector<T> other_vector) {
    if (this->_size != other_vector._size)
        throw std::invalid_argument("Vectors have different sizes");

    T result = T();
    for (int i = 0; i < _size; i++)
        result += this->_vec[i] * other_vector[i];

    return result;
}

template <class T>
MathVector<T> MathVector<T>::operator=(const MathVector<T> other_vector) {
    if (&other_vector == this)
        return *this;

    this->_size = other_vector._size;
    this->_capacity = other_vector._capacity;
    this->_vec = new T[this->_capacity];
    this->_status = new Status[this->_capacity];
    this->_start_index = other_vector._start_index;

    for (int i = 0; i < this->_capacity; i++) {
        if (i < other_vector._size) {
            this->_vec[i] = other_vector._vec[i];
            this->_status[i] = other_vector._status[i];
        }
        else this->_status[i] = Status::Empty;
    }

    return *this;
}

#endif // !MATHVECTOR_MATHVECTOR_H
