#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include "../lib_TVector/tvector.h"
#include "../lib_ITable/itable.h"
#include <algorithm>

#define SIZE 100

enum status { busy, empty, deleted };

template <class TValue>
struct HashData {
    status _state;
    std::string _key;
    TValue _value;

    HashData(const std::string& key = "", const TValue& value = TValue(), const status& state = empty) :
        _key(key), _value(value), _state(state) {}

    HashData& operator=(const HashData& other) {
        this->_state = other._state;
        this->_key = other._key;
        this->_value = other._value;

        return *this;
    }
};

template <class TValue>
class HashTable : ITable<std::string, TValue> {
    TVector<HashData<TValue>> _rows;
    size_t _size;
    size_t _shift;
    size_t _count;

public:
    HashTable(size_t size = SIZE) : _rows(size), _size(size), _count(0) {
        for (size_t i = std::max( size_t(2), size / 15); i < size; i++) {
            if (is_simple(i, size)) {
                _shift = i;
                return;
            }
        }
    }

    inline bool is_empty() const noexcept { return _count == 0; }
    inline bool is_full() const noexcept { return _count == _size; }
    TValue* find(const std::string&) const noexcept { return nullptr; }
    void insert(const std::string&, const TValue&);
    void erase(const std::string&);

    friend std::ostream& operator<<(std::ostream& out, const HashTable& table) {
        int i = 0, k = 0;
        while (k < table._count) {
            if (table._rows[i]._state == busy) {
                out << table._rows[i]._key << ": " << table._rows[i]._value << std::endl;
                k++;
            }
            i++;
        }

        return out;
    }

private:
    size_t h(const std::string&) const noexcept;
    size_t hh(size_t) const noexcept;

    size_t gcd(size_t a, size_t b) const noexcept;
    bool is_simple(size_t, size_t) const noexcept;
};

template <class TValue>
size_t HashTable<TValue>::h(const std::string& key) const noexcept {
    size_t  hash = 0;
    for (int i = 0; i < key.size(); i++)
        hash += key[i];

    hash %= _size;
    return hash;
}

template <class TValue>
size_t HashTable<TValue>::hh(size_t hash) const noexcept {
    return (hash + _shift) % _size;
}

template <class TValue>
void HashTable<TValue>::insert(const std::string& key, const TValue& value) {
    if (is_full())
        throw std::logic_error("Table is full");

    size_t hash = h(key);

    while (true) {
        if (_rows[hash]._state != busy) {
            _rows[hash] = HashData<TValue>(key, value, busy);
            _count++;
            return;
        }
        else if (_rows[hash]._key == key)
            throw std::invalid_argument("This key already exists");

        hash = hh(hash);
    }
}

template <class TValue>
void HashTable<TValue>::erase(const std::string& key) {
    size_t hash = h(key);
    size_t first_hash = hash;

    while (true) {
        if (_rows[hash]._state == empty)
            break;

        if (_rows[hash]._state == busy && _rows[hash]._key == key) {
            _rows[hash]._state = deleted;
            _count--;
            return;
        }

        if (first_hash == hash)
            break;

        hash = hh(hash);
    }

    throw std::invalid_argument("This key wasn't found");
}

template <class TValue>
bool HashTable<TValue>::is_simple(size_t first, size_t second) const noexcept {
    return gcd(first, second) == 1;
}

template <class TValue>
size_t HashTable<TValue>::gcd(size_t first, size_t second) const noexcept {
    if (first == second) return first;
    if (first > second) return gcd(first - second, second);
    return gcd(first, second - first);
}

#endif // !HASHTABLE_HASHTABLE_H
