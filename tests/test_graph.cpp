#include <gtest/gtest.h>
#include "../lib_ListGraph/listgraph.h"

TEST(TestListGraphLib, test_constructor) {
    // not weighted graph
    std::vector<std::pair<int, int>> edges;
    edges.push_back(std::pair<int, int>(0, 3));
    edges.push_back(std::pair<int, int>(0, 5));
    edges.push_back(std::pair<int, int>(0, 2));
    edges.push_back(std::pair<int, int>(1, 2));
    edges.push_back(std::pair<int, int>(2, 3));
    ListGraph<int> graph(edges);  // not oriented
    ASSERT_NO_THROW(ListGraph<int> graph(edges, true));  // oriented

    // weighted graph
    std::vector<std::pair<std::pair<int, int>, int>> weighted_edges;
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 3), 2));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 5), 7));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(5, 2), 4));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(1, 2), 3));
    weighted_edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(2, 3), 10));
    ASSERT_NO_THROW(ListGraph<int> graph(weighted_edges));  // not oriented
    ASSERT_NO_THROW(ListGraph<int> graph(weighted_edges, true));  // oriented
}

TEST(TestListGraphLib, test_add_existing_edge) {
    std::vector<std::pair<std::pair<int, int>, int>> edges;
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 3), 2));
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 5), 7));
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(2, 3), 10));
    ListGraph<int> graph(edges);

    ASSERT_ANY_THROW(graph.add_edge(0, 3, 5));
}

TEST(TestListGraphLib, test_add_non_existent_edge) {
    std::vector<std::pair<std::pair<int, int>, int>> edges;
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 3), 2));
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(0, 5), 7));
    edges.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(2, 3), 10));
    ListGraph<int> graph(edges);

    ASSERT_ANY_THROW(graph.add_edge(1, 4, 8));
}