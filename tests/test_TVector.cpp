#include <gtest/gtest.h>
#include "tvector.h"

TEST(TestTVectorLib, test_default_constructor) {
    ASSERT_NO_THROW(TVector<int> vec);
}

TEST(TestTVectorLib, test_initialize_constructor) {
    ASSERT_NO_THROW(TVector<int> vec(5));
}

TEST(TestTVectorLib, test_convert_mass_to_tvector) {
    ASSERT_NO_THROW(TVector<int> vec({1, 2, 3, 4, 5}));
}

TEST(TestTVectorLib, test_copy_vector) {
    TVector<int> vec1({ 1, 2, 3, 4, 5 });
    ASSERT_NO_THROW(TVector<int> vec2(vec1));
}

TEST(TestTVectorLib, test_get_size) {
    size_t expected_result = 5;
    TVector<int> vec(5);
    size_t actual_result = vec.size();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_get_capacity) {
    size_t expected_result = 15;
    TVector<int> vec(5);
    size_t actual_result = vec.capacity();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_get_data) {
    int* expected_result = new int[5];
    for (int i = 0; i < 5; i++) expected_result[i] = i + 1;
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int* actual_result = vec.data();

    for (int i = 0; i < 5; i++)
        ASSERT_EQ(expected_result[i], actual_result[i]);
}

TEST(TestTVectorLib, test_get_iterator_begin) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int mass[5] = { 1, 2, 3, 4, 5 };
    int* expected_result = std::begin(mass);
    int* actual_result = vec.begin();

    ASSERT_EQ(*expected_result, *actual_result);
}

TEST(TestTVectorLib, test_get_iterator_end) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int mass[5] = { 1, 2, 3, 4, 5 };
    int* expected_result = std::end(mass) - 1;
    int* actual_result = vec.end() - 1;

    ASSERT_EQ(*expected_result, *actual_result);
}

TEST(TestTVectorLib, test_get_front) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = 1;
    int actual_result = vec.front();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_get_back) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = 5;
    int actual_result = vec.back();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_is_empty_if_full) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    bool expected_result = false;
    bool actual_result = vec.is_empty();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_is_empty_if_empty) {
    TVector<int> vec;
    bool expected_result = true;
    bool actual_result = vec.is_empty();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_clear_vector) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    bool expected_result = true;
    vec.clear();
    bool actual_result = vec.is_empty();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_push_back_without_reset_memory) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = 6;
    vec.push_back(6);
    int actual_result = *(vec.end() - 1);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_push_back_with_reset_memory) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 });
    int expected_result = 15;
    vec.push_back(15);
    int actual_result = *(vec.end() - 1);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_push_front_without_reset_memory) {
    TVector<int> vec({ 2, 3, 4, 5 });
    int expected_result = 1;
    vec.push_front(1);
    int actual_result = *(vec.begin());

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_push_front_with_reset_memory) {
    TVector<int> vec({ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 1;
    vec.push_front(1);
    int actual_result = *(vec.begin());

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_pop_back_without_reset_memory) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 14;
    vec.pop_back();
    int actual_result = *(vec.end() - 1);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_pop_back_with_reset_memory) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = 2;
    vec.pop_front();
    int actual_result = *(vec.begin());

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_pop_front_without_reset_memory) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 2;
    vec.pop_front();
    int actual_result = vec[0];

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_pop_front_with_reset_memory) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = 2;
    vec.pop_front();
    int actual_result = *(vec.begin());

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_push_back_after_pop_front) {
    TVector<int> vec({ 1, 2, 3, 4 });
    int expected_result = 5;
    vec.pop_front();
    vec.push_back(5);
    int actual_result = *(vec.end() - 1);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_push_front_after_pop_back) {
    TVector<int> vec({ 1, 2, 3, 4 });
    int expected_result = 5;
    vec.pop_front();
    vec.push_back(5);
    int actual_result = *(vec.end() - 1);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_erase_without_reset_memory) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 14;
    vec.erase(vec.begin() + 2);
    int actual_result = vec.size();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_erase_with_reset_memory) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = 4;
    vec.erase(vec.begin() + 2);
    int actual_result = *(vec.begin() + 2);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_push_back_after_erase_with_reset_memory) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = 6;
    vec.erase(vec.begin() + 1);
    vec.push_back(6);
    int actual_result = vec.back();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_push_front_after_erase_with_reset_memory) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = 0;
    vec.erase(vec.begin() + 1);
    vec.push_front(0);
    int actual_result = vec.front();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_push_back_after_erase_without_reset_memory) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 16;
    vec.erase(vec.begin() + 2);
    vec.push_back(16);
    int actual_result = vec.back();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_insert_without_reset_memory) {
    TVector<int> vec({ 1, 2, 4, 5 });
    int expected_result = 3;
    vec.insert(vec.begin() + 2, 3);
    int actual_result = *(vec.begin() + 2);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_insert_with_reset_memory) {
    TVector<int> vec({ 1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 30;
    vec.insert(vec.begin() + 2, 3);
    int actual_result = vec.capacity();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_insert_after_pop_front) {
    TVector<int> vec({ 1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 3;
    vec.pop_front();
    vec.insert(vec.begin() + 1, 3);
    int actual_result = vec[1];

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_insert_after_erase) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 3;
    vec.erase(vec.begin() + 1);
    vec.insert(vec.begin() + 3, 3);
    int actual_result = vec[3];

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_find) {
    TVector<int> vec({ 1, 2, 2, 3, 4 });
    int expected_result = 1;
    int actual_result = find(vec, 2);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_find_non_existent_element) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = -1;
    int actual_result = find(vec, 6);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_find_element_after_erase) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 3;
    vec.erase(vec.begin() + 2);
    int actual_result = find(vec, 5);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_find_element_after_insert) {
    TVector<int> vec({ 1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 2;
    vec.insert(vec.begin() + 2, 3);
    int actual_result = find(vec, 3);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_find_deleted_element) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = -1;
    vec.erase(vec.begin() + 2);
    int actual_result = find(vec, 3);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_find_last_element) {
    TVector<int> vec({ 1, 2, 2, 3, 4 });
    int expected_result = 2;
    int actual_result = find_last(vec, 2);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_find_non_existent_last_element) {
    TVector<int> vec({ 1, 2, 2, 3, 4 });
    int expected_result = -1;
    int actual_result = find_last(vec, 5);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_find_last_element_after_erase) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 4;
    vec.erase(vec.begin() + 5);
    int actual_result = find_last(vec, 5);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_find_last_element_after_insert) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 3;
    vec.insert(vec.begin() + 2, 3);
    int actual_result = find_last(vec, 3);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_find_last_deleted_element) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = -1;
    vec.erase(vec.begin() + 2);
    int actual_result = find_last(vec, 3);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_find_all_elements) {
    TVector<int> vec({ 1, 2, 3, 2, 4, 2 });
    int* expected_result = new int[3];
    for (int i = 0; i < 3; i++)
        expected_result[i] = 2 * i + 1;
    int* actual_result = find_all(vec, 2);

    for (int i = 0; i < 3; i++)
        ASSERT_EQ(expected_result[i], actual_result[i]);
}

TEST(TestTVectorLib, test_find_all_non_existent_elements) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int* expected_result = nullptr;
    int* actual_result = find_all(vec, 6);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_find_all_after_erase) {
    TVector<int> vec({ 1, 2, 3, 2, 4, 2 });
    int* expected_result = new int[3];
    expected_result[0] = 1;
    expected_result[1] = 2;
    expected_result[2] = 4;
    vec.erase(vec.begin() + 2);

    int* actual_result = find_all(vec, 2);
    for (int i = 0; i < 3; i++)
        ASSERT_EQ(expected_result[i], actual_result[i]);
}

TEST(TestTVectorLib, test_find_all_after_insert) {
    TVector<int> vec({ 1, 2, 3, 2, 4, 2 });
    int* expected_result = new int[4];
    expected_result[0] = 1;
    expected_result[1] = 2;
    expected_result[2] = 4;
    expected_result[3] = 6;

    vec.insert(vec.begin() + 2, 2);
    int* actual_result = find_all(vec, 2);

    for (int i = 0; i < 3; i++)
        ASSERT_EQ(expected_result[i], actual_result[i]);
}

TEST(TestTVectorLib, test_find_all_with_deleted_element) {
    TVector<int> vec({ 1, 2, 3, 2, 4, 2 });
    int* expected_result = new int[2];
    expected_result[0] = 1;
    expected_result[1] = 4;

    vec.erase(vec.begin() + 3);
    int* actual_result = find_all(vec, 2);

    for (int i = 0; i < 2; i++)
        ASSERT_EQ(expected_result[i], actual_result[i]);
}

TEST(TestTVectorLib, test_emplace_by_value) {
    TVector<int> vec({ 1, 2, 3, 2, 4, 2 });
    int* expected_result = new int[3];
    for (int i = 0; i < 3; i++)
        expected_result[i] = 2 * i + 1;

    vec.emplace(2, 5);
    int* actual_result = find_all(vec, 5);

    for (int i = 0; i < 3; i++)
        ASSERT_EQ(expected_result[i], actual_result[i]);
}

TEST(TestTVectorLib, test_emplace_by_value_non_existent_element) {
    TVector<int> vec({ 1, 2, 3, 2, 4, 2 });
    int* expected_result = nullptr;
    vec.emplace(5, 6);
    int* actual_result = find_all(vec, 6);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_emplace_by_value_deleted_element) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = -1;

    vec.erase(vec.begin() + 2);
    vec.emplace(3, 20);
    int actual_result = find(vec, 20);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_emplace_by_index) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = 5;
    vec.emplace(vec.begin() + 2, 5);
    int actual_result = *(vec.begin() + 2);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_emplace_by_index_element_out_of_range) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    ASSERT_ANY_THROW(vec.emplace(vec.begin() + 5, 5));
}

TEST(TestTVectorLib, test_emplace_by_index_after_erase) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = -1;

    vec.erase(vec.begin() + 2);
    vec.emplace(vec.begin() + 5, 20);
    int actual_result = find(vec, 7);

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_assign) {
    TVector<int> vec1({ 1, 2, 3, 4, 5 }), vec2;
    int* expected_result = new int[5];
    for (int i = 0; i < 5; i++)
        expected_result[i] = i + 1;

    vec2.assign(vec1);
    int* actual_result = vec2.data();
    for (int i = 0; i < 5; i++)
        ASSERT_EQ(expected_result[i], actual_result[i]);
}

TEST(TestTVectorLib, test_assign_null_vector) {
    TVector<int>* vec1 = NULL, vec2;
    ASSERT_ANY_THROW(vec2.assign(*vec1));
}

TEST(TestTVectorLib, test_at) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = 3;

    int actual_result = vec.at(2);
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_at_after_erase) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 7;

    vec.erase(vec.begin() + 2);
    int actual_result = vec.at(5);
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_at_after_insert) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 5;

    vec.insert(vec.begin() + 2, 20);
    int actual_result = vec.at(5);
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_at_deleted_elem) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 4;

    vec.erase(vec.begin() + 2);
    int actual_result = vec.at(2);
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_at_after_pop_front) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 2;

    vec.pop_front();
    int actual_result = vec.at(0);
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_at_after_pop_back) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 14;

    vec.pop_back();
    int actual_result = vec.at(vec.size() - 1);
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_shrink_to_fit) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = 5;

    vec.shrink_to_fit();
    int actual_result = vec.capacity();
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_shrink_to_fit_after_erase) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 14;

    vec.erase(vec.begin() + 2);
    vec.shrink_to_fit();
    int actual_result = vec.capacity();
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_resize_to_less) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = 3;

    vec.resize(3);
    int actual_result = vec.size();
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_resize_to_less_after_erase) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 10;

    vec.erase(vec.begin() + 2);
    vec.resize(10);
    int actual_result = vec.size();
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_resize_to_more) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = 10;

    vec.resize(10);
    int actual_result = vec.size();
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_resize_to_more_with_reset_memory) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    int expected_result = 15;

    vec.resize(15);
    int actual_result = vec.size();
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_resize_to_more_after_erase) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int expected_result = 17;

    vec.erase(vec.begin() + 2);
    vec.resize(17);
    int actual_result = vec.size();
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_shuffle) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    int* expected_result = new int[10];
    for (int i = 0; i < 10; i++)
        expected_result[i] = i + 1;
    shuffle(vec);
    int* actual_result = vec.data();

    bool result = false;
    for (int i = 0; i < vec.size(); i++)
        result |= (expected_result[i] != actual_result[i]);
    ASSERT_TRUE(result);
}

TEST(TestTVectorLib, test_shuffle_after_erase) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int* expected_result = new int[10];
    for (int i = 0; i < 10; i++)
        expected_result[i] = i + 1;

    vec.erase(vec.begin() + 2);
    shuffle(vec);
    int* actual_result = vec.data();

    bool result = false;
    for (int i = 0; i < vec.size(); i++)
        result |= (expected_result[i] != actual_result[i]);
    ASSERT_TRUE(result);
}

TEST(TestTVectorLib, test_sort) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    int* expected_result = new int[10];
    for (int i = 0; i < 10; i++)
        expected_result[i] = i + 1;

    shuffle(vec);
    sort_vector(vec);
    int* actual_result = vec.data();
    for (int i = 0; i < vec.size(); i++)
        ASSERT_EQ(expected_result[i], actual_result[i]);
}

TEST(TestTVectorLib, test_sort_after_erase) {
    TVector<int> vec({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    int* expected_result = new int[15];
    for (int i = 0; i < 15; i++)
        expected_result[i] = i + 1;

    vec.erase(vec.begin() + 2);
    shuffle(vec);
    sort_vector(vec);
    int* actual_result = vec.data();
    for (int i = 0; i < vec.size(); i++)
        ASSERT_EQ(expected_result[i], actual_result[i]);
}

TEST(TestTVectorLib, test_operator_compare_if_equal) {
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }),
        vec2({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    bool expected_result = true;

    bool actual_result = vec1 == vec2;
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_operator_compare_if_not_equal) {
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 9 }),
        vec2({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    bool expected_result = false;

    bool actual_result = vec1 == vec2;
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_operator_compare_after_erase) {
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }),
        vec2({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    bool expected_result = false;

    vec1.erase(vec1.begin() + 2);
    bool actual_result = vec1 == vec2;
    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_second_operator_compare_if_equal) {
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }),
        vec2({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    bool expected_result = false;
    bool actual_result = vec1 != vec2;

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_second_operator_compare_if_not_equal) {
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 9 }),
        vec2({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    bool expected_result = true;
    bool actual_result = vec1 != vec2;

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_second_operator_compare_after_erase) {
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }),
        vec2({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    bool expected_result = true;

    vec1.erase(vec1.begin() + 2);
    bool actual_result = vec1 != vec2;

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_second_operator_compare_after_erase_if_equal) {
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }),
        vec2({ 1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
    bool expected_result = false;

    vec2.erase(vec2.begin() + 2);
    bool actual_result = vec1 != vec2;

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_at_negative_index) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    ASSERT_ANY_THROW(int num = vec.at(-1));
}

TEST(TestTVectorLib, test_operator_index) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = 3;
    int actual_result = vec[2];

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_operator_index_out_of_range) {
    TVector<int> vec({ 1, 2, 3, 4, 5 });
    int expected_result = 5;
    int actual_result = vec[5];
    ASSERT_NE(expected_result, actual_result);
}

TEST(TestTVectorLib, test_insert_into_an_empty_vector) {
    TVector<int> vec1;
    vec1.push_front(1);
    TVector<int> res1({ 1 });
    TVector<int> vec2;
    vec2.push_back(10);
    TVector<int> res2({ 10 });
    TVector<int> vec3;
    vec3.insert(0, 88);
    TVector<int> res3({ 88 });
    bool expected_result = true;
    bool actual_result = false;
    if ((vec1 == res1) && (vec2 == res2) && (vec3 == res3))
        actual_result = true;

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_reserve) {
    TVector<int> vec;
    vec.reserve(20);
    int expected_result = 20;
    int actual_result = vec.capacity();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_delete_last_element) {
    TVector<int> vec({ 1 });
    vec.erase(vec.begin());
    int expected_result = 0;
    int actual_result = vec.size();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_insert_element_after_delete_last) {
    TVector<int> vec({ 1 });
    vec.erase(vec.begin());
    vec.insert(vec.begin(), 2);
    int expected_result = 2;
    int actual_result = vec[0];

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_shrink_to_fit_empty_vector) {
    TVector<int> vec;
    size_t expected_result = 0;
    vec.shrink_to_fit();
    size_t actual_result = vec.capacity();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_add_element_after_shrink_to_fit) {
    TVector<int> vec;
    size_t expected_result = 1;
    vec.shrink_to_fit();
    vec.insert(vec.begin(), 1);
    size_t actual_result = vec.size();

    ASSERT_EQ(expected_result, actual_result);
}

TEST(TestTVectorLib, test_iterator_in_empty_list) {
    TVector<int> list;
    TVector<int>::Iterator it;
    bool enterCycle = false;
    for (it = list.begin(); it != list.end(); it++) {
        enterCycle = true;
    }
    ASSERT_FALSE(enterCycle);
}

TEST(TestTVectorLib, test_iterator_for_read) {
    TVector<int> vec;
    for (int i = 0; i < 5; i++)
        vec.push_back(i + 1);

    TVector<int>::Iterator it = vec.begin();
    int i = 0;
    for (it = vec.begin(); it != vec.end(); it++) {
        ASSERT_EQ(*it, ++i);
    }
}

TEST(TestTVectorLib, test_iterator_for_write) {
    TVector<int> vec;
    for (int i = 0; i < 5; i++)
        vec.push_back(0);

    TVector<int>::Iterator it = vec.begin();
    for (it; it != vec.end(); it++);

    int i = 5;
    while (true) {
        *it = i;
        ASSERT_EQ(*it, i--);
        if (it == vec.begin()) break;
        --it;
    }
}

TEST(TestTVectorLib, test_iterator_for_operator_add_and_assign) {
    TVector<int> vec;
    for (int i = 0; i < 5; i++)
        vec.push_back(i + 1);

    TVector<int>::Iterator it = vec.begin();
    it += 3;
    ASSERT_EQ(*it, 4);
}

TEST(TestTVectorLib, test_iterator_for_operator_sub_and_assign) {
    TVector<int> vec;
    for (int i = 0; i < 5; i++)
        vec.push_back(i + 1);

    TVector<int>::Iterator it = vec.begin();
    for (int i = 0; i < 3; i++) it++;

    it -= 3;
    ASSERT_EQ(*it, 1);
}