#ifndef HASHTABLEC_HASHTABLEC_H
#define HASHTABLEC_HASHTABLEC_H

#include "../lib_ITable/itable.h"
#include "../lib_list/list.h"
#include "../lib_TVector/tvector.h"

#define SIZE 100
#define KEY_WIDTH 10
#define VALUE_WIDTH 50

template <class TValue>
struct HashCData {
    std::string _key;
    TValue _value;

    HashCData(const std::string& key = "", const TValue& value = TValue()) :
        _key(key), _value(value){}

    HashCData& operator=(const HashCData& other) {
        this->_key = other._key;
        this->_value = other._value;

        return *this;
    }
};

template <class TValue>
class HashTableC : ITable<std::string, TValue> {
    TVector<List<HashCData<TValue>>> _rows;
    size_t _size;
    size_t _count;

public:
    HashTableC(size_t size = SIZE);

    inline bool is_empty() const noexcept { return _count == 0; }
    TValue* find(const std::string&) const noexcept;
    void insert(const std::string&, const TValue&);
    void erase(const std::string&);

    friend std::ostream& operator<<(std::ostream& out, const HashTableC& table) {
        // head
        std::cout << "+----------+";
        for (int i = 0; i < VALUE_WIDTH; i++) std::cout << "-";

        std::cout << "+" << std::endl << "| Key      | Value";
        for (int i = 0; i < VALUE_WIDTH - 6; i++) std::cout << " ";
        std::cout << "|" << std::endl;

        std::cout << "+----------+";
        for (int i = 0; i < VALUE_WIDTH; i++) std::cout << "-";
        std::cout << "+" << std::endl;

        for (int i = 0; i < table._rows.size(); i++) {
            if (table._rows[i].is_empty())
                continue;

            for (auto it = table._rows[i].begin(); it != table._rows[i].end(); it++) {
                std::ostringstream key_out, value_out;
                key_out << (*it)._key;
                value_out << (*it)._value;
                std::string key = key_out.str(), value = value_out.str();

                // row
                std::cout << "| " << key;
                for (int i = 0; i < KEY_WIDTH - key.size() - 1; i++) std::cout << " ";
                std::cout << "| " << value;
                for (int i = 0; i < VALUE_WIDTH - value.size() - 1; i++) std::cout << " ";
                std::cout << "|" << std::endl;

                // border
                std::cout << "+----------+";
                for (int i = 0; i < VALUE_WIDTH; i++) std::cout << "-";
                std::cout << "+" << std::endl;
            }
        }

        return out;
    }

private:
    size_t h(const std::string&) const noexcept;
    Node<HashCData<TValue>>* find_prev_node(const std::string) const noexcept;
};

template <class TValue>
HashTableC<TValue>::HashTableC(size_t size) : _size(size), _count(0), _rows(size) {}

template <class TValue>
TValue* HashTableC<TValue>::find(const std::string& key) const noexcept {
    Node<HashCData<TValue>>* node = find_prev_node(key);

    if (node && node->_value._key == key) return &node->_value._value;  // if key == head
    if (node) return &node->_next->_value._value;
    return nullptr;
}

template <class TValue>
void HashTableC<TValue>::insert(const std::string& key, const TValue& value) {
    if (find(key))
        throw std::invalid_argument("This key already exists");

    size_t hash = h(key);
    _rows[hash].push_back(HashCData<TValue>(key, value));
}

template <class TValue>
void HashTableC<TValue>::erase(const std::string& key) {
    Node<HashCData<TValue>>* node = find_prev_node(key);
    if (!node)
        throw std::invalid_argument("This key wasn't found");

    size_t hash = h(key);
    if (node->_value._key == key)
        _rows[hash].pop_front();
    else
        _rows[hash].erase(node);
}

template <class TValue>
size_t HashTableC<TValue>::h(const std::string& key) const noexcept {
    size_t  hash = 0;
    for (int i = 0; i < key.size(); i++)
        hash += key[i];

    hash %= _size;
    return hash;
}

template <class TValue>
Node<HashCData<TValue>>* HashTableC<TValue>::find_prev_node(const std::string key) const noexcept {
    size_t hash = h(key);

    Node<HashCData<TValue>>* curr = _rows[hash].head();
    if (curr && curr->_value._key == key)  // if key == list.head
        return curr;

    while (curr) {
        if (curr->_next && curr->_next->_value._key == key)
            return curr;

        curr = curr->_next;
    }

    return nullptr;
}

#endif // !HASHTABLEC_HASHTABLEC_H
