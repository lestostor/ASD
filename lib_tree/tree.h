#ifndef TREE_TREE_H
#define TREE_TREE_H

#include "../lib_queue/queue.h"
#include <iostream>

template <class TKey, class TValue>
struct Node {
    std::pair<TKey, TValue> _data;
    Node<TKey, TValue>* _left;
    Node<TKey, TValue>* _right;

    Node<TKey, TValue>(const TKey& key, const TValue& value, Node<TKey, TValue>* left = nullptr, Node<TKey, TValue>* right = nullptr) :
        _data(key, value), _left(left), _right(right) {}
};

template <class TKey, class TValue>
class Tree {
    Node<TKey, TValue>* _root;

public:
    Tree(Node<TKey, TValue>* root = nullptr);
    ~Tree();

    void insert(const TKey&, const TValue&);
    TValue* find(const TKey&) const noexcept;
    void erase(const TKey&);
    inline bool is_empty() const noexcept { return _root == nullptr; }
    void clear() noexcept;

    inline Node<TKey, TValue>* root() const noexcept { return _root; }

    void print_w() const noexcept;
    void print_lcr() const noexcept;
    void print_lrc() const noexcept;
    void print_clr() const noexcept;
    void print_tree() const noexcept;

private:
    void print_lcr_rec(Node<TKey, TValue>*) const noexcept;
    void print_clr_rec(Node<TKey, TValue>*) const noexcept;
    void print_lrc_rec(Node<TKey, TValue>*) const noexcept;
    void print_lines(int, int) const noexcept;
    Node<TKey, TValue>* find_rec(const TKey&, Node<TKey, TValue>*) const;
    Node<TKey, TValue>* find_last_parent() const;
};

template <class TKey, class TValue>
Tree<TKey, TValue>::Tree(Node<TKey, TValue>* root) : _root(root) {}

template <class TKey, class TValue>
Tree<TKey, TValue>::~Tree() {
    clear();
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    Node<TKey, TValue>* node = new Node<TKey, TValue>(key, value);

    if (is_empty()) {
        _root = node;
        return;
    }

    Node<TKey, TValue>* curr = nullptr;
    Queue<Node<TKey, TValue>*> q;
    q.push(_root);
    while (true) {
        curr = q.head();
        q.pop();
        if (!curr->_left) {
            curr->_left = node;
            return;
        }
        if (!curr->_right) {
            curr->_right = node;
            return;
        }

        q.push(curr->_left);
        q.push(curr->_right);
    }
}

template <class TKey, class TValue>
TValue* Tree<TKey, TValue>::find(const TKey& key) const noexcept {
    Node<TKey, TValue>* res = find_rec(key, _root);
    if (res)
        return &(res->_data.second);
    return nullptr;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::erase(const TKey& key) {
    Node<TKey, TValue>* deleted = find_rec(key, _root);
    if (!deleted)
        throw std::invalid_argument("This key wasn't found");
    Node<TKey, TValue>* last_parent = find_last_parent(), *last = nullptr;

    if (last_parent->_right) {
        last = last_parent->_right;
        last_parent->_right = nullptr;
    }
    else if (last_parent->_left) {
        last = last_parent->_left;
        last_parent->_left = nullptr;
    }

    deleted->_data = last->_data;
    delete last;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear() noexcept {
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
void Tree<TKey, TValue>::print_w() const noexcept {
    if (is_empty()) return;

    Queue<Node<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        Node<TKey, TValue>* curr = q.head();
        std::cout << curr->_data.second << " ";
        q.pop();

        if (curr->_left)
            q.push(curr->_left);
        if (curr->_right)
            q.push(curr->_right);
    }
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_clr() const noexcept {
    print_clr_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lcr() const noexcept {
    print_lcr_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lrc() const noexcept {
    print_lrc_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_tree() const noexcept {
    if (_root == nullptr) return;

    Queue<Node<TKey, TValue>*> q;
    q.push(_root);

    int level = 0;
    while (!q.is_empty()) {
        int size = q.size(), count = 2 * size;
        std::cout << std::string(30 - level * 5, ' ');

        for (int i = 0; i < size; i++) {
            Node<TKey, TValue>* node = q.head();
            q.pop();

            std::cout << node->_data.first;
            if (i % 2 == 0)
                std::cout << "        ";
            else
                std::cout << " ";

            if (node->_left)
                q.push(node->_left);
            else
                count--;
            if (node->_right)
                q.push(node->_right);
            else
                count--;
        }
        std::cout << std::endl;

        if (!q.is_empty())
            print_lines(level, count);

        level++;
    }
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_clr_rec(Node<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    std::cout << node->_data.second << " ";
    print_clr_rec(node->_left);
    print_clr_rec(node->_right);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lcr_rec(Node<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_lcr_rec(node->_left);
    std::cout << node->_data.second << " ";
    print_lcr_rec(node->_right);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lrc_rec(Node<TKey, TValue>* node) const noexcept {
    if (node == nullptr) return;

    print_lrc_rec(node->_left);
    print_lrc_rec(node->_right);
    std::cout << node->_data.second << " ";
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lines(int level, int count) const noexcept {
    std::cout << std::string(30 - level * 5 - 2, ' ');
    for (int i = 0; i < count; i++) {
        if (i % 2 == 0)
            std::cout << "/  ";
        else
            std::cout << "\\      ";
    }
    std::cout << std::endl;
}

template <class TKey, class TValue>
Node<TKey, TValue>* Tree<TKey, TValue>::find_rec(const TKey& key, Node<TKey, TValue>* node) const {
    if (node && node->_data.first == key) return node;

    Node<TKey, TValue>* found_node = nullptr;
    if (node && node->_left)
        found_node = find_rec(key, node->_left);
    if (node && node->_right && !found_node)
        found_node = find_rec(key, node->_right);

    return found_node;
}

template <class TKey, class TValue>
Node<TKey, TValue>* Tree<TKey, TValue>::find_last_parent() const {
    Node<TKey, TValue>* curr = nullptr, * parent = nullptr;
    Queue<Node<TKey, TValue>*> q;
    q.push(_root);

    while (!q.is_empty()) {
        curr = q.head();
        q.pop();

        if (curr->_left) {
            q.push(curr->_left);
            parent = curr;
        }
        if (curr->_right) {
            q.push(curr->_right);
            parent = curr;
        }
    }

    return parent;
}

#endif // !TREE_TREE_H
