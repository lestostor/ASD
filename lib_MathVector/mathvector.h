#ifndef MATHVECTOR_MATHVECTOR_H
#define MATHVECTOR_MATHVECTOR_H

#include "../lib_TVector/tvector.h"
#include <initializer_list>

template <class T>
class MathVector : TVector<T> {
    int _start_index;

public:
    MathVector() {};
    MathVector(const int) {};
    MathVector(std::initializer_list<T>) {};
    MathVector(const MathVector&) {};
};

#endif // !MATHVECTOR_MATHVECTOR_H
