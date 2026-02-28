#ifndef UNSORTEDlISTTABLE_UNSORTEDLISTTABLE_H
#define UNSORTEDlISTTABLE_UNSORTEDLISTTABLE_H

#include "../lib_ITable/itable.h"
#include "../lib_list/list.h"
#include <sstream>

#define KEY_WIDTH 10
#define VALUE_WIDTH 50

template <class TKey, class TValue>
class UnsortedListTable : ITable<TKey, TValue> {
    List<std::pair<TKey, TValue>> _rows;
public:
    UnsortedListTable();
    ~UnsortedListTable() {}

    void insert(const TKey&, const TValue&);
    void erase(const TKey&);
    TValue* find(const TKey&) const noexcept;
    bool inline is_empty() const noexcept { return _rows.is_empty(); }

    friend std::ostream& operator<<(std::ostream& out, const UnsortedListTable& table) {
        // head
        std::cout << "+----------+";
        for (int i = 0; i < VALUE_WIDTH; i++) std::cout << "-";

        std::cout << "+" << std::endl << "| Key      | Value";
        for (int i = 0; i < VALUE_WIDTH - 6; i++) std::cout << " ";
        std::cout << "|" << std::endl;

        std::cout << "+----------+";
        for (int i = 0; i < VALUE_WIDTH; i++) std::cout << "-";
        std::cout << "+" << std::endl;

        for (auto it = table._rows.begin(); it != table._rows.end(); it++) {
            std::ostringstream key_out, value_out;
            key_out << (*it).first;
            value_out << (*it).second;
            std::string key = key_out.str(), value = value_out.str();

            // row
            std::cout << "| " << key;
            for (int i = 0; i < KEY_WIDTH - key.size() - 1; i++) std::cout << " ";
            std:: cout << "| " << value;
            for (int i = 0; i < VALUE_WIDTH - value.size() - 1; i++) std::cout << " ";
            std::cout << "|" << std::endl;

            // border
            std::cout << "+----------+";
            for (int i = 0; i < VALUE_WIDTH; i++) std::cout << "-";
            std::cout << "+" << std::endl;
        }

        return out;
    }
};

template <class TKey, class TValue>
UnsortedListTable<TKey, TValue>::UnsortedListTable() : _rows() {}

template <class TKey, class TValue>
void UnsortedListTable<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    std::pair<TKey, TValue> row = std::pair<TKey, TValue>(key, value);
    if (find(key) != nullptr)
        throw std::invalid_argument("This key already exists");
    _rows.push_back(row);
}

template <class TKey, class TValue>
void UnsortedListTable<TKey, TValue>::erase(const TKey& key) {
    Node<std::pair<TKey, TValue>>* node = _rows.head();

    while (node != nullptr) {
        if (node->_next != nullptr && node->_next->_value.first == key) {
            _rows.erase(node);
            return;
        }

        node = node->_next;
    }

    throw std::logic_error("This key wasn't found");
}

template <class TKey, class TValue>
TValue* UnsortedListTable<TKey, TValue>::find(const TKey& key) const noexcept {
    for (auto it = _rows.begin(); it != _rows.end(); it++) {
        if ((*it).first == key)
            return &((*it).second);
    }
    return nullptr;
}

#endif // !UNSORTEDlISTTABLE_UNSORTEDLISTTABLE_H
