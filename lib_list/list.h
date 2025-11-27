#ifndef LIST_LIST_H
#define LIST_LIST_H

template <class T>
struct Node {
    T _value;
    Node<T>* _prev;
    Node<T>* _next;

    Node(T value, Node<T>* next = nullptr, Node<T>* prev = nullptr) : _value(value), _next(next), _prev(prev) {}
};

template <class T>
class List {
protected:
    Node<T>* _head, * _tail;
    int _count;

public:
    List();
    List(const List<T>&);
    ~List();

    class Iterator {
    protected:
        Node<T>* _current;

    public:
        Iterator() : _current(nullptr) {}
        Iterator(Node<T>* node) : _current(node) {}

        Iterator& operator++() {  // ++it
            _current = _current->_next;
            return *this;
        }
        Iterator operator++(int) {  // it++
            Iterator tmp(_current);
            _current = _current->_next;
            return tmp;
        }
        Iterator& operator=(const Iterator& other) {
            this->_current = other._current;
            return *this;
        }
        bool operator!=(const Iterator& other) {
            return _current != other._current;
        }

        bool operator==(const Iterator& other) {
            return _current == other._current;
        }

        T& operator*() {
            return _current->_value;
        }
    };

    inline Node<T>* head() const noexcept{
        return _head;
    }
    inline Node<T>* tail() const noexcept {
        return _tail;
    }

    inline int get_size() const noexcept {
        return _count;
    }

    Iterator begin() {
        return _head;
    }

    Iterator end() {
        if (_tail == nullptr) return nullptr;
        return _tail->_next;
    }

    bool is_empty() const noexcept;

    void push_front(const T&) noexcept;
    void push_back(const T&) noexcept;
    void insert(size_t, const T&);
    void insert(Node<T>*, const T&);

    void pop_back();
    void pop_front();
    void erase(size_t);
    void erase(Node<T>*);

    List<T>& operator=(const List<T>&);
};

template <class T>
List<T>::List() {
    _head = nullptr;
    _tail = nullptr;
    _count = 0;
}

template <class T>
List<T>::List(const List<T>& other) {
    if (other._count == 0) {
        _head = nullptr;
        _tail = nullptr;
        _count = 0;
        return;
    }
    _count = 0;
    Node<T>* cur = other._head;
    while (cur != nullptr) {
        push_back(cur->_value);
        cur = cur->_next;
        if (this->_count == other._count && cur != nullptr) {
            Node<T>* enter = cur, *cur = other._head, *node = _head;
            while (cur != enter) {
                cur = cur->_next;
                node = node->_next;
            }
            _tail->_next = node;
            break;
        }
    }
}

template <class T>
bool List<T>::is_empty() const noexcept {
    return _head == nullptr;
}

template <class T>
void List<T>::push_front(const T& value) noexcept {
    Node<T>* node = new Node<T>(value, _head);
    if (is_empty())
        _tail = node;
    _head = node;
    _count++;
}

template <class T>
void List<T>::push_back(const T& value) noexcept {
    _count++;
    Node<T>* node = new Node<T>(value);
    if (_count == 1) {
        _head = node;
        _tail = node;
        return;
    }
    _tail->_next = node;
    _tail = node;
}

template <class T>
void List<T>::insert(Node<T>* node, const T& value) {
    if (node == nullptr)
        throw std::invalid_argument("Null node");
    if (is_empty())
        throw std::logic_error("List is empty");
    Node<T>* new_node = new Node<T>(value, node->_next);
    node->_next = new_node;
    if (node == _tail)
        _tail = new_node;
    _count++;
}

template <class T>
void List<T>::insert(size_t pos, const T& value) {
    if (pos == 0) {
        push_front(value);
        return;
    }
    if (pos == _count) {
        push_back(value);
        return;
    }
    Node<T>* cur = _head;
    size_t cur_pos = 0;
    while (cur != nullptr) {
        if (cur_pos == pos - 1)
            break;
        cur_pos++;
        cur = cur->_next;
    }
    if (cur == nullptr)
        throw std::invalid_argument("Wrong position");
    insert(cur, value);
}

template <class T>
void List<T>::pop_back() {
    if (is_empty())
        throw std::logic_error("List is empty");
    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        _count--;
        return;
    }
    Node<T>* cur = _head;
    while (cur->_next != _tail)
        cur = cur->_next;
    delete _tail;
    _tail = cur;
    cur->_next = nullptr;
    _count--;
}

template <class T>
void List<T>::pop_front() {
    if (is_empty())
        throw std::logic_error("List is empty");

    _count--;
    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        return;
    }
    Node<T>* node = _head->_next;
    delete _head;
    _head = node;
}

template <class T>
List<T>::~List() {
    while (_head != nullptr) {
        Node<T>* node = _head;
        _head = _head->_next;
        delete node;
    }
}

template <class T>
void List<T>::erase(Node<T>* node) {
    if (node == nullptr)
        throw std::invalid_argument("Null node");
    if (is_empty())
        throw std::logic_error("List is empty");

    _count--;
    Node<T>* del = node->_next, *new_node = del->_next;
    node->_next = new_node;
    if (del == _tail)
        _tail = node;
    delete del;
}

template <class T>
void List<T>::erase(size_t pos) {
    if (pos == 0) {
        pop_front();
        return;
    }
    if (pos == _count - 1) {
        pop_back();
        return;
    }
    Node<T>* cur = _head;
    size_t cur_pos = 0;
    while (cur != nullptr) {
        if (cur_pos == pos - 1)
            break;
        cur_pos++;
        cur = cur->_next;
    }
    if (cur == nullptr)
        throw std::invalid_argument("Wrong position");
    erase(cur);
}

template <class T>
List<T>& List<T>::operator=(const List<T>& other) {
    this->_count = 0;
    Node<T>* cur = other._head;
    while (cur != nullptr) {
        push_back(cur->_value);
        cur = cur->_next;
        if (this->_count == other._count && cur != nullptr) {
            Node<T>* enter = cur, * cur = other._head, * node = _head;
            while (cur != enter) {
                cur = cur->_next;
                node = node->_next;
            }
            _tail->_next = node;
            break;
        }
    }
    return *this;
}

#endif // !LIST_LIST_H