#ifndef MATRIXGRAPH_MATRIXGRAPH_H
#define MATRIXGRAPH_MATRIXGRAPH_H

#include "../lib_TriangleMatrix/trianglematrix.h"
#include <vector>
#include <set>
#include <limits>

template <class T>
class MatrixGraph {
    Matrix<int> _graph;
    std::vector<T> _data;
    bool _is_oriented;
    bool _is_weighted;

public:
    MatrixGraph(std::vector<std::pair<std::pair<T, T>, int>> data, bool is_oriented = false);
    MatrixGraph(std::vector<std::pair<T, T>> data, bool is_oriented = false);

    void add_edge(const T& data1, const T& data2, size_t weight = 1);
    void delete_edge(const T&, const T&);
    void delete_vertex(const T&);

private:
    int find_vertex(const T&) const noexcept;
    bool is_edge_exist(const int, const int) const noexcept;
};

template <class T>
MatrixGraph<T>::MatrixGraph(std::vector<std::pair<std::pair<T, T>, int>> data, bool is_oriented) : _data(),
    _is_oriented(is_oriented), _is_weighted(true) {
    std::set<T> vertecies;
    for (int i = 0; i < data.size(); i++) {
        vertecies.insert(data[i].first.first);
        vertecies.insert(data[i].first.second);
    }

    if (!_is_oriented)
        _graph = TriangleMatrix<int>(vertecies.size());
    else _graph = Matrix<int>(vertecies.size(), vertecies.size());

    for (int i = 0; i < _graph.get_lines(); i++)
        for (int j = 0; j < _graph.get_columns(); j++)
            _graph[i][j] = INT_MAX;

    for (int i = 0; i < data.size(); i++)
        add_edge(data[i].first.first, data[i].first.second, data[i].second);
}

template <class T>
MatrixGraph<T>::MatrixGraph(std::vector<std::pair<T, T>> data, bool is_oriented) : _data(),
    _is_oriented(is_oriented), _is_weighted(false) {
    std::set<T> vertecies;
    for (int i = 0; i < data.size(); i++) {
        vertecies.insert(data[i].first);
        vertecies.insert(data[i].second);
    }

    if (!_is_oriented)
        _graph = TriangleMatrix<int>(vertecies.size());
    else _graph = Matrix<int>(vertecies.size(), vertecies.size());

    for (int i = 0; i < _graph.get_lines(); i++)
        for (int j = 0; j < _graph.get_columns(); j++)
            _graph[i][j] = 0;

    for (int i = 0; i < data.size(); i++)
        add_edge(data[i].first, data[i].second);
}

template <class T>
void MatrixGraph<T>::add_edge(const T& data1, const T& data2, size_t weight) {
    int vert1 = find_vertex(data1), vert2 = find_vertex(data2);

    if (vert1 == -1 && vert2 == -1 && !_data.empty())
        throw std::invalid_argument("This vertecies doesn't exist");

    if (vert1 != -1 && vert2 != -1 && is_edge_exist(vert1, vert2))
        throw std::invalid_argument("This edge already exist");

    if (vert1 == -1) {
        vert1 = _data.size();
        _data.push_back(data1);
    }
    if (vert2 == -1) {
        vert2 = _data.size();
        _data.push_back(data2);
    }

    _graph[vert1][vert2] = weight;
}

template <class T>
void MatrixGraph<T>::delete_edge(const T& data1, const T& data2) {
    int vert1 = find_vertex(data1), vert2 = find_vertex(data2);

    if (vert1 == -1 || vert2 == -1)
        throw std::invalid_argument("Vertex doesn't exists");

    if (!is_edge_exist(vert1, vert2))
        throw std::invalid_argument("This edge doesn't exist");

    int first, second;
    if (!_is_oriented)
        first = std::min(vert1, vert2), second = std::max(vert1, vert2);
    else first = vert1, second = vert2;

    if (_is_weighted)
        _graph[first][second] = INT_MAX;
    else _graph[first][second] = 0;
}

template <class T>
void MatrixGraph<T>::delete_vertex(const T& vertex) {
    int ind = find_vertex(vertex);

    if (ind == -1)
        throw std::invalid_argument("Vertex doesn't exists");

    int null;
    if (_is_weighted)
        null = INT_MAX;
    else null = 0;

    for (int i = 0; i < _graph[ind].size(); i++) {
        _graph[ind][i] = null;
        _graph[i][ind] = null;
    }
}

template <class T>
int MatrixGraph<T>::find_vertex(const T& vertex) const noexcept {
    for (int i = 0; i < _data.size(); i++) {
        if (_data[i] == vertex)
            return i;
    }

    return -1;
}

template <class T>
bool MatrixGraph<T>::is_edge_exist(const int vert1, const int vert2) const noexcept {
    int first, second;
    if (!_is_oriented)
        first = std::min(vert1, vert2), second = std::max(vert1, vert2);
    else first = vert1, second = vert2;

    return _is_weighted && _graph[first][second] != INT_MAX ||
        !_is_weighted && _graph[first][second] == 1;
}

#endif // !MATRIXGRAPH_MATRIXGRAPH_H
