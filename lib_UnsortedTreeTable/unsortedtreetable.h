#ifndef UNSORTEDTREETABLE_UNSORTEDTREETABLE_H
#define UNSORTEDTREETABLE_UNSORTEDTREETABLE_H

#include "../lib_ITable/itable.h"
#include "../lib_tree/tree.h"

template <class TKey, class TValue>
class UnsortedTreeTable : ITable<TKey, TValue> {
    Tree<TKey, TValue> _rows;

public:
    UnsortedTreeTable();
    ~UnsortedTreeTable() {}

    void insert(const TKey&, const TValue&);
    inline void erase(const TKey& key) { _rows.erase(key); }
    inline TValue* find(const TKey& key) const noexcept { return _rows.find(key); }
    inline bool is_empty() const noexcept { return _rows.is_empty(); }
};

template <class TKey, class TValue>
UnsortedTreeTable<TKey, TValue>::UnsortedTreeTable() : _rows() {}

template <class TKey, class TValue>
void UnsortedTreeTable<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    if (_rows.find(key))
        throw std::invalid_argument("This key already exists");

    _rows.insert(key, value);
}

#endif // !UNSORTEDTREETABLE_UNSORTEDTREETABLE_H
