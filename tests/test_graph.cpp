#include <gtest/gtest.h>
#include "../lib_ListGraph/listgraph.h"
#include "../lib_MatrixGraph/matrixgraph.h"

// ListGraph

TEST(TestListGraphLib, test_constructor) {
    // not weighted graph
    std::vector<std::pair<int, int>> edges;
    edges.push_back(std::pair<int, int>(0, 3));
    edges.push_back(std::pair<int, int>(0, 5));
    edges.push_back(std::pair<int, int>(0, 2));
    edges.push_back(std::pair<int, int>(1, 2));
    edges.push_back(std::pair<int, int>(2, 3));
    edges.push_back(std::pair<int, int>(3, 5));
    ASSERT_NO_THROW(ListGraph<int> graph(edges));  // not oriented
    edges.push_back(std::pair<int, int>(3, 2));
    ASSERT_NO_THROW(ListGraph<int> graph(edges, true));  // oriented

    // weighted graph
    std::vector<std::pair<std::pair<int, int>, int>> weighted_edges;
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(3, 0), 2));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 5), 7));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(5, 2), 4));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(1, 2), 3));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(2, 3), 10));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(3, 5), 5));
    ASSERT_NO_THROW(ListGraph<int> graph(weighted_edges));  // not oriented
    ASSERT_NO_THROW(ListGraph<int> graph(weighted_edges, true));  // oriented
}

TEST(TestListGraphLib, test_add_existing_edge) {
    std::vector<std::pair<std::pair<int, int>, int>> edges;
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 3), 2));
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 5), 7));
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(2, 3), 10));
    ListGraph<int> graph(edges);

    ASSERT_ANY_THROW(graph.add_edge(0, 3, 2));
}

TEST(TestListGraphLib, test_add_non_existent_edge) {
    std::vector<std::pair<std::pair<int, int>, int>> edges;
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 3), 2));
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 5), 7));
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(2, 3), 10));
    ListGraph<int> graph(edges);

    ASSERT_ANY_THROW(graph.add_edge(1, 4, 8));
}

TEST(TestListGraphLib, test_find_min_way) {
    // not weighted graph
    std::vector<std::pair<int, int>> edges;
    edges.push_back(std::pair<int, int>(0, 3));
    edges.push_back(std::pair<int, int>(0, 5));
    edges.push_back(std::pair<int, int>(0, 2));
    edges.push_back(std::pair<int, int>(1, 2));
    edges.push_back(std::pair<int, int>(2, 3));
    edges.push_back(std::pair<int, int>(3, 5));

    ListGraph<int> graph(edges);
    std::vector<Vertex<int>*> way = find_min_way(graph, 1, 5);
    ASSERT_EQ(way[0]->_value, 1);
    ASSERT_EQ(way[1]->_value, 2);
    ASSERT_EQ(way[2]->_value, 0);
    ASSERT_EQ(way[3]->_value, 5);

    // weighted graph
    std::vector<std::pair<std::pair<int, int>, int>> weighted_edges;
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(3, 0), 2));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 5), 7));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(5, 2), 4));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(1, 2), 3));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(2, 3), 10));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(3, 5), 5));

    ListGraph<int> weighted_graph(edges);
    way = find_min_way(weighted_graph, 3, 1);
    ASSERT_EQ(way[0]->_value, 3);
    ASSERT_EQ(way[1]->_value, 2);
    ASSERT_EQ(way[2]->_value, 1);
}

TEST(TestListGraphLib, test_delete_edge) {
    std::vector<std::pair<int, int>> edges;
    edges.push_back(std::pair<int, int>(0, 3));
    edges.push_back(std::pair<int, int>(0, 5));
    edges.push_back(std::pair<int, int>(0, 2));
    edges.push_back(std::pair<int, int>(1, 2));
    edges.push_back(std::pair<int, int>(2, 3));
    edges.push_back(std::pair<int, int>(3, 5));

    ListGraph<int> graph1(edges);
    graph1.delete_edge(0, 5);
    ASSERT_NO_THROW(graph1.add_edge(0, 5));
    ASSERT_ANY_THROW(graph1.delete_edge(1, 3));
    ASSERT_ANY_THROW(graph1.delete_edge(4, 7));  // non existent vertex

    ListGraph<int> graph2(edges, true);
    graph2.add_edge(5, 0);
    graph2.delete_edge(0, 5);
    ASSERT_NO_THROW(graph2.add_edge(0, 5));
    ASSERT_ANY_THROW(graph1.delete_edge(4, 7));
    ASSERT_ANY_THROW(graph2.delete_edge(2, 1));  // wrong direction
}

TEST(TestListGraphLib, test_delete_vertex) {
    std::vector<std::pair<int, int>> edges;
    edges.push_back(std::pair<int, int>(0, 3));
    edges.push_back(std::pair<int, int>(0, 5));
    edges.push_back(std::pair<int, int>(0, 2));
    edges.push_back(std::pair<int, int>(1, 2));
    edges.push_back(std::pair<int, int>(2, 3));
    edges.push_back(std::pair<int, int>(3, 5));

    ListGraph<int> graph1(edges);
    graph1.delete_vertex(0);
    ASSERT_NO_THROW(graph1.add_edge(0, 3));
    ASSERT_NO_THROW(graph1.add_edge(0, 2));
    ASSERT_NO_THROW(graph1.add_edge(0, 5));

    ListGraph<int> graph2(edges, true);
    graph2.delete_vertex(3);
    ASSERT_NO_THROW(graph2.add_edge(0, 3));
    ASSERT_NO_THROW(graph2.add_edge(2, 3));
    ASSERT_NO_THROW(graph2.add_edge(3, 5));
}

// MatrixGraph

TEST(TestMatrixGraphLib, test_constructor) {
    // not weighted graph
    std::vector<std::pair<int, int>> edges;
    edges.push_back(std::pair<int, int>(0, 3));
    edges.push_back(std::pair<int, int>(0, 5));
    edges.push_back(std::pair<int, int>(0, 2));
    edges.push_back(std::pair<int, int>(1, 2));
    edges.push_back(std::pair<int, int>(2, 3));
    edges.push_back(std::pair<int, int>(3, 5));
    ASSERT_NO_THROW(MatrixGraph<int> graph(edges));  // not oriented
    edges.push_back(std::pair<int, int>(3, 2));
    ASSERT_NO_THROW(MatrixGraph<int> graph(edges, true));  // oriented

    //// weighted graph
    std::vector<std::pair<std::pair<int, int>, int>> weighted_edges;
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(3, 0), 2));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 5), 7));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(5, 2), 4));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(1, 2), 3));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(2, 3), 10));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(3, 5), 5));
    ASSERT_NO_THROW(MatrixGraph<int> graph(weighted_edges));  // not oriented
    ASSERT_NO_THROW(MatrixGraph<int> graph(weighted_edges, true));  // oriented
}

TEST(TestMatrixGraphLib, test_add_existing_edge) {
    std::vector<std::pair<std::pair<int, int>, int>> edges;
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 3), 2));
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 5), 7));
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(2, 3), 10));
    MatrixGraph<int> graph(edges);

    ASSERT_ANY_THROW(graph.add_edge(0, 3, 2));
}

TEST(TestMatrixGraphLib, test_add_non_existent_edge) {
    std::vector<std::pair<std::pair<int, int>, int>> edges;
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 3), 2));
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 5), 7));
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(2, 3), 10));
    MatrixGraph<int> graph(edges);

    ASSERT_ANY_THROW(graph.add_edge(1, 4, 8));
}

TEST(TestMatrixGraphLib, test_delete_edge) {
    std::vector<std::pair<int, int>> edges;
    edges.push_back(std::pair<int, int>(0, 3));
    edges.push_back(std::pair<int, int>(0, 5));
    edges.push_back(std::pair<int, int>(0, 2));
    edges.push_back(std::pair<int, int>(1, 2));
    edges.push_back(std::pair<int, int>(2, 3));
    edges.push_back(std::pair<int, int>(3, 5));

    MatrixGraph<int> graph1(edges);
    graph1.delete_edge(0, 5);
    ASSERT_NO_THROW(graph1.add_edge(0, 5));
    ASSERT_ANY_THROW(graph1.delete_edge(1, 3));
    ASSERT_ANY_THROW(graph1.delete_edge(4, 7));  // non existent vertex

    MatrixGraph<int> graph2(edges, true);
    graph2.add_edge(5, 0);
    graph2.delete_edge(0, 5);
    ASSERT_NO_THROW(graph2.add_edge(0, 5));
    ASSERT_ANY_THROW(graph1.delete_edge(4, 7));
    ASSERT_ANY_THROW(graph2.delete_edge(2, 1));  // wrong direction
}

TEST(TestMatrixGraphLib, test_delete_vertex) {
    std::vector<std::pair<int, int>> edges;
    edges.push_back(std::pair<int, int>(0, 3));
    edges.push_back(std::pair<int, int>(0, 5));
    edges.push_back(std::pair<int, int>(0, 2));
    edges.push_back(std::pair<int, int>(1, 2));
    edges.push_back(std::pair<int, int>(2, 3));
    edges.push_back(std::pair<int, int>(3, 5));

    MatrixGraph<int> graph1(edges);
    graph1.delete_vertex(0);
    ASSERT_NO_THROW(graph1.add_edge(0, 3));
    ASSERT_NO_THROW(graph1.add_edge(0, 2));
    ASSERT_NO_THROW(graph1.add_edge(0, 5));

    MatrixGraph<int> graph2(edges, true);
    graph2.delete_vertex(3);
    ASSERT_NO_THROW(graph2.add_edge(0, 3));
    ASSERT_NO_THROW(graph2.add_edge(2, 3));
    ASSERT_NO_THROW(graph2.add_edge(3, 5));
}
