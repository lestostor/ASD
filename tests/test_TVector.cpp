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
