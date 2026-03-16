#ifndef UNSORTEDTREETABLE_UNSORTEDTREETABLE_H
#define UNSORTEDTREETABLE_UNSORTEDTREETABLE_H

#include "../lib_ITable/itable.h"
#include "../lib_tree/tree.h"
#include <iostream>

#define KEY_WIDTH 10
#define VALUE_WIDTH 50

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

    friend std::ostream& operator<<(std::ostream& out, const UnsortedTreeTable<TKey, TValue>& table) {
        if (table.is_empty()) return out;

        // head
        out << "+----------+";
        for (int i = 0; i < VALUE_WIDTH; i++) out << "-";

        out << "+" << std::endl << "| Key      | Value";
        for (int i = 0; i < VALUE_WIDTH - 6; i++) out << " ";
        out << "|" << std::endl;

        out << "+----------+";
        for (int i = 0; i < VALUE_WIDTH; i++) out << "-";
        std::cout << "+" << std::endl;

        Queue<Node<TKey, TValue>*> q;
        q.push(table._rows.root());

        while (!q.is_empty()) {
            Node<TKey, TValue>* curr = q.head();

            std::ostringstream key_out, value_out;
            key_out << curr->_data.first;
            value_out << curr->_data.second;
            std::string key = key_out.str(), value = value_out.str();

            // row
            out << "| " << key;
            for (int i = 0; i < KEY_WIDTH - key.size() - 1; i++) out << " ";
            out << "| " << value;
            for (int i = 0; i < VALUE_WIDTH - value.size() - 1; i++) out << " ";
            out << "|" << std::endl;

            // border
            out << "+----------+";
            for (int i = 0; i < VALUE_WIDTH; i++) out << "-";
            out << "+" << std::endl;

            q.pop();

            if (curr->_left)
                q.push(curr->_left);
            if (curr->_right)
                q.push(curr->_right);
        }

        return out;
    }
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
