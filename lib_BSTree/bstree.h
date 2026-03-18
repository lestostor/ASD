#ifndef BSTREE_BSTREE_H
#define BSTREE_BSTREE_H

#include <iostream>
#include "../lib_queue/queue.h"

template <class TKey, class TValue>
struct Node {
    std::pair<TKey, TValue> _data;
    Node<TKey, TValue>* _left;
    Node<TKey, TValue>* _right;

    Node<TKey, TValue>(const TKey& key, const TValue& value, Node<TKey, TValue>* left = nullptr, Node<TKey, TValue>* right = nullptr) :
        _data(key, value), _left(left), _right(right) {}
};

template <class TKey, class TValue>
class BSTree {
    Node<TKey, TValue>* _root;

public:
    BSTree(Node<TKey, TValue>* root = nullptr);
    ~BSTree();

    inline bool is_empty() const noexcept { return _root == nullptr; }
    TValue* find(const TKey&) const noexcept;
    void insert(const TKey&, const TValue&);
    void erase(const TKey&);
    void print() const noexcept;
private:
    Node<TKey, TValue>* find_parent(const TKey&) const noexcept;
    void print_rec(Node<TKey, TValue>*) const noexcept;
    void delete_node(Node<TKey, TValue>*&) noexcept;
    Node<TKey, TValue>* find_max_left(Node<TKey, TValue>*) const noexcept;
};

template <class TKey, class TValue>
BSTree<TKey, TValue>::BSTree(Node<TKey, TValue>* root) : _root(root) {}

template <class TKey, class TValue>
BSTree<TKey, TValue>::~BSTree() {
    if (is_empty()) return;

    Queue<Node<TKey, TValue>*> q;
    q.push(_root);
    Node<TKey, TValue>* curr = nullptr;

    while (!q.is_empty()) {
        curr = q.head();
        Node<TKey, TValue>* deleted = curr;
        q.pop();
        if (curr->_left)
            q.push(curr->_left);
        if (curr->_right)
            q.push(curr->_right);

        delete deleted;
    }

    _root = nullptr;
}

template <class TKey, class TValue>
TValue* BSTree<TKey, TValue>::find(const TKey& key) const noexcept {
    Node<TKey, TValue>* parent = find_parent(key);

    if (!parent)
        return nullptr;
    if (parent->_left && parent->_left->_data.first == key)
        return &parent->_left->_data.second;
    if (parent->_right && parent->_right->_data.first == key)
        return &parent->_right->_data.second;
    if (parent == _root)
        return &_root->_data.second;

    return nullptr;
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    Node<TKey, TValue>* parent = find_parent(key);
    if (!parent) {
        _root = new Node<TKey, TValue> (key, value);
        return;
    }
    if (parent->_data.first < key && !parent->_right) {
        parent->_right = new Node<TKey, TValue> (key, value);
        return;
    }
    if (parent->_data.first > key && !parent->_left) {
        parent->_left = new Node<TKey, TValue> (key, value);
        return;
    }

    throw std::invalid_argument("This key already exists");
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::erase(const TKey& key) {
    Node<TKey, TValue>* parent = find_parent(key);

    if (parent->_right && parent->_right->_data.first == key)
        delete_node(parent->_right);
    else if (parent->_left && parent->_left->_data.first == key)
        delete_node(parent->_left);
    else if (parent == _root)
        delete_node(_root);
    else
        throw std::invalid_argument("This key wasn't found");
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print() const noexcept {
    print_rec(_root);
}

template <class TKey, class TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::find_parent(const TKey& key) const noexcept {
    if (is_empty()) return nullptr;

    if (_root->_data.first == key) return _root;

    Node<TKey, TValue>* curr = _root;

    while (true) {
        if (curr->_data.first > key) {
            if (!curr->_left)  // parent for insert
                return curr;
            if (curr->_left && curr->_left->_data.first == key)  // parent for find
                return curr;
            curr = curr->_left;
        }
        else {
            if (!curr->_right)
                return curr;
            if (curr->_right && curr->_right->_data.first == key)
                return curr;
            curr = curr->_right;
        }
    }

}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::print_rec(Node<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_rec(node->_left);
    std::cout << node->_data.second << " ";
    print_rec(node->_right);
}

template <class TKey, class TValue>
void BSTree<TKey, TValue>::delete_node(Node<TKey, TValue>*& node) noexcept {
    if (!node->_left && !node->_right) {
        delete node;
        node = nullptr;
    }
    else if (!node->_left) {
        Node<TKey, TValue>* deleted = node;
        node = node->_right;
        delete deleted;
    }
    else if (!node->_right) {
        Node<TKey, TValue>* deleted = node;
        node = node->_left;
        delete deleted;
    }
    else {
        Node<TKey, TValue>* max_left = find_max_left(node), *parent = find_parent(max_left->_data.first);
        node->_data = max_left->_data;
        if (parent->_left == max_left) {
            delete max_left;
            parent->_left = nullptr;
        }
        else {
            delete max_left;
            parent->_right = nullptr;
        }
    }
}

template <class TKey, class TValue>
Node<TKey, TValue>* BSTree<TKey, TValue>::find_max_left(Node<TKey, TValue>* node) const noexcept {
    Node<TKey, TValue>* curr = node->_left, *max = curr;

    while (curr) {
        if (curr->_data.first > max->_data.first)
            max = curr;
        curr = curr->_right;
    }

    return max;
}

#endif // !BSTREE_BSTREE_H
