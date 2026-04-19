#ifndef LISTGRAPH_LISTGRAPH_H
#define LISTGRAPH_LISTGRAPH_H

#include "../lib_list/list.h"
#include <iostream>
#include <vector>

template <class T>
struct Vertex {
    T _value;
    List<std::pair<Vertex<T>*, size_t>> _edges;

    Vertex(const T& val) : _value(val), _edges() {}
};

template <class T>
class ListGraph {
    std::vector<Vertex<T>*> _graph;
    bool _is_oriented;
    bool _is_weighted;

public:
    ListGraph(std::vector<std::pair<std::pair<T, T>, int>> data, bool is_oriented = false);
    ListGraph(std::vector<std::pair<T, T>> data, bool is_oriented = false);

    void add_edge(const T& data1, const T& data2, size_t weight = 1);
    void delete_edge(const T&, const T&);
    void delete_vertex(const T&);

private:
    Vertex<T>* find_vertex(const T&) noexcept;
    bool is_edge_exist(Vertex<T>*, Vertex<T>*) noexcept;
};

template <class T>
ListGraph<T>::ListGraph(std::vector<std::pair<std::pair<T, T>, int>> data, bool is_oriented) :
    _graph(), _is_oriented(is_oriented), _is_weighted(true) {
    for (int i = 0; i < data.size(); i++)
        add_edge(data[i].first.first, data[i].first.second, data[i].second);
}

template <class T>
ListGraph<T>::ListGraph(std::vector<std::pair<T, T>> data, bool is_oriented) :
    _graph(), _is_oriented(is_oriented), _is_weighted(false) {
    for (int i = 0; i < data.size(); i++)
        add_edge(data[i].first, data[i].second);
}

template <class T>
void ListGraph<T>::add_edge(const T& data1, const T& data2, size_t weight) {
    Vertex<T>* vertex1 = find_vertex(data1);
    Vertex<T>* vertex2 = find_vertex(data2);

    if (vertex1 && vertex2 && is_edge_exist(vertex1, vertex2))
        throw std::invalid_argument("This edge already exists");

    if (!vertex1 && !vertex2 && !_graph.empty())
        throw std::invalid_argument("There must be at least one vertex");

    if (!vertex1) {
        vertex1 = new Vertex<T>(data1);
        _graph.push_back(vertex1);
    }
    if (!vertex2) {
        vertex2 = new Vertex<T>(data2);
        _graph.push_back(vertex2);
    }

    vertex1->_edges.push_back(std::pair<Vertex<T>*, size_t>(vertex2, weight));

    if (!_is_oriented)
        vertex2->_edges.push_back(std::pair<Vertex<T>*, size_t>(vertex1, weight));
}

template <class T>
Vertex<T>* ListGraph<T>::find_vertex(const T& vertex) noexcept {
    for (int i = 0; i < _graph.size(); i++) {
        if (_graph[i]->_value == vertex)
            return _graph[i];
    }

    return nullptr;
}

template <class T>
bool ListGraph<T>::is_edge_exist(Vertex<T>* vertex1, Vertex<T>* vertex2) noexcept {
    for (auto it = vertex1->_edges.begin(); it != vertex1->_edges.end(); it++) {
        if ((*it).first->_value == vertex2->_value)
            return true;
    }

    return false;
}

#endif // !LISTGRAPH_LISTGRAPH_H
