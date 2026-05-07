#include <gtest/gtest.h>
#include "hashtable.h"
#include "hashtablec.h"

TEST(TestHashTableLib, test_constructor) {
    HashTable<int> table(50);
    ASSERT_TRUE(table.is_empty());
}

TEST(TestHashTableLib, test_insert) {
    HashTable<int> table(5);

    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);
    ASSERT_ANY_THROW(table.insert("one", 4));

    table.insert("four", 4);
    table.insert("five", 5);

    ASSERT_EQ(*table.find("one"), 1);
    ASSERT_EQ(*table.find("two"), 2);
    ASSERT_EQ(*table.find("three"), 3);
    ASSERT_EQ(*table.find("four"), 4);
    ASSERT_EQ(*table.find("five"), 5);

    ASSERT_ANY_THROW(table.insert("six", 6));  // if table is full

    //std::cout << table;
    //system("pause");
}

TEST(TestHashTableLib, test_erase) {
    HashTable<int> table(30);

    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);
    table.insert("oen", 1);

    table.erase("oen");

    ASSERT_EQ(table.find("oen"), nullptr);

    ASSERT_ANY_THROW(table.erase("oen"));
}

// HashTableC

TEST(TestHashTableCLib, test_constructor) {
    HashTableC<int> table(50);
    ASSERT_TRUE(table.is_empty());
}

TEST(TestHashTableCLib, test_insert) {
    HashTableC<int> table(5);

    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);
    ASSERT_ANY_THROW(table.insert("one", 4));

    table.insert("four", 4);
    table.insert("five", 5);

    ASSERT_EQ(*table.find("one"), 1);
    ASSERT_EQ(*table.find("two"), 2);
    ASSERT_EQ(*table.find("three"), 3);
    ASSERT_EQ(*table.find("four"), 4);
    ASSERT_EQ(*table.find("five"), 5);

    //std::cout << table;
    //system("pause");
}

TEST(TestHashTableCLib, test_erase) {
    HashTableC<int> table(30);

    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);
    table.insert("oen", 1);

    table.erase("one");

    ASSERT_EQ(table.find("one"), nullptr);
    ASSERT_EQ(*table.find("oen"), 1);
    ASSERT_ANY_THROW(table.erase("one"));

    table.insert("one", 1);
    table.erase("one");
    ASSERT_EQ(table.find("one"), nullptr);
}
