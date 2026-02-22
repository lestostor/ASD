#ifndef ITABLE_ITABLE_H
#define ITABLE_ITABLE_H

#include <iostream>

template <class TKey, class TValue>
class ITable {
public:
    virtual void insert(const TKey&, const TValue&) = 0;
    virtual void erase(const TKey&) = 0;
    virtual TValue* find(const TKey&) const noexcept = 0;
    virtual inline bool is_empty() const noexcept = 0;

    friend std::ostream& operator<<(std::ostream& out, const ITable&) {};
};

#endif // !ITABLE_ITABLE_H
