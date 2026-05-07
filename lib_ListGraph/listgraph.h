#ifndef LISTGRAPH_LISTGRAPH_H
#define LISTGRAPH_LISTGRAPH_H

#include "../lib_list/list.h"
#include "../lib_PriorityQueue/priorityqueue.h"
#include <iostream>
#include <vector>
#include <limits>

template <class T>
struct Vertex {
    T _value;
    int _ind;
    List<std::pair<Vertex<T>*, size_t>> _edges;

    Vertex(const T& val, int ind) : _value(val), _ind(ind), _edges() {}
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

    friend std::vector<Vertex<T>*> find_min_way(ListGraph& graph, const T& x, const T& y) {
        std::vector<bool> vertecies(graph._graph.size());
        std::vector<int> d(graph._graph.size(), INT_MAX);
        std::vector<int> prev(graph._graph.size(), -1);
        PriotityQueue<int> min_lenghts;
        int order = 1;

        Vertex<T>* start = graph.find_vertex(x);
        Vertex<T>* end = graph.find_vertex(y);
        d[start->_ind] = 0;
        min_lenghts.push(0, start->_ind, order++);  // ind, lenght

        while (!min_lenghts.is_empty()){
            int curr = min_lenghts.pop().get_value();
    
            Vertex<T>* vertex = graph._graph[curr];
            vertecies[curr] = true;
    
            for (auto it = vertex->_edges.begin(); it != vertex->_edges.end(); it++, order++) {
                int ind = (*it).first->_ind, lenght = (*it).second;
                if (vertecies[ind])
                    continue;

                if (d[curr] + lenght < d[ind]) {
                    d[ind] = d[curr] + lenght;
                    prev[ind] = curr;
                    min_lenghts.push(d[ind], ind, order);
                }
            }
        }
    
        return graph.find_way(prev, start->_ind, end->_ind);
    }

private:
    Vertex<T>* find_vertex(const T&) noexcept;
    bool is_edge_exist(Vertex<T>*, Vertex<T>*) noexcept;
    std::vector<Vertex<T>*> find_way(const std::vector<T>&, int, int) const noexcept;
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
        vertex1 = new Vertex<T>(data1, _graph.size());
        _graph.push_back(vertex1);
    }
    if (!vertex2) {
        vertex2 = new Vertex<T>(data2, _graph.size());
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

template <class T>
std::vector<Vertex<T>*> ListGraph<T>::find_way(const std::vector<T>& prev, int start, int end) const noexcept {
    std::vector<Vertex<T>*> way;
    int i = end;

    while (i != -1) {
        way.insert(way.begin(), _graph[i]);
        i = prev[i];
    }

    return way;
}

template <class T>
void ListGraph<T>::delete_edge(const T& first, const T& second) {
    Vertex<T>* vert1 = find_vertex(first), * vert2 = find_vertex(second);

    int i = 0;

    if (!is_edge_exist(vert1, vert2))
        throw std::invalid_argument("This edge doesn't exist");

    for (auto it = vert1->_edges.begin(); it != vert1->_edges.end(); it++, i++) {
        if ((*it).first == vert2) {
            vert1->_edges.erase(i);
            break;
        }
    }

    if (_is_oriented)
        return;

    i = 0;
    for (auto it = vert2->_edges.begin(); it != vert2->_edges.end(); it++, i++) {
        if ((*it).first == vert1) {
            vert2->_edges.erase(i);
            return;
        }
    }
}

template <class T>
void ListGraph<T>::delete_vertex(const T& vertex) {
    Vertex<T>* vert = find_vertex(vertex);
    if (!vert)
        throw std::invalid_argument("This vertex doesn't exist");

    for (int i = 0; i < _graph.size(); i++) {
        if (i == vert->_ind) {
            vert->_edges.clear();
            continue;
        }

        int j = 0;
        for (auto it = _graph[i]->_edges.begin(); it != _graph[i]->_edges.end(); it++, j++) {
            if ((*it).first == vert) {
                _graph[i]->_edges.erase(j);
                break;
            }
        }
    }

}

#endif // !LISTGRAPH_LISTGRAPH_H
