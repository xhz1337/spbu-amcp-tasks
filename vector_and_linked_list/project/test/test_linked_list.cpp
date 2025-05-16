#include "linked_list.hpp"
#include <gtest/gtest.h>

using mmh::DoublyLinkedList;

TEST(DoublyLinkedListTest, ConstructorCreatesEmptyList) {   
    DoublyLinkedList<int> list;
    EXPECT_EQ(list.get_size(), 0);
}

TEST(DoublyLinkedListTest, PushBackIncreasesSize) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    EXPECT_EQ(list.get_size(), 1);
    list.push_back(20);
    EXPECT_EQ(list.get_size(), 2);
}

TEST(DoublyLinkedListTest, HasItemFindsElements) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    EXPECT_TRUE(list.has_item(10));
    EXPECT_TRUE(list.has_item(20));
    EXPECT_TRUE(list.has_item(30));
    EXPECT_FALSE(list.has_item(40));
}

TEST(DoublyLinkedListTest, RemoveFirstElement) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    EXPECT_TRUE(list.remove_first(20));
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_FALSE(list.has_item(20));
}

TEST(DoublyLinkedListTest, RemoveNonExistentElementFails) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    
    EXPECT_FALSE(list.remove_first(20));
    EXPECT_EQ(list.get_size(), 1);
}

TEST(DoublyLinkedListTest, RemoveFirstItem) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    
    EXPECT_TRUE(list.remove_first(10));
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_TRUE(list.has_item(20));
}

TEST(DoublyLinkedListTest, RemoveLastItem) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    
    EXPECT_TRUE(list.remove_first(20));
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_TRUE(list.has_item(10));
}

TEST(DoublyLinkedListTest, PrintEmptyList) {
    DoublyLinkedList<int> list;
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}

TEST(DoublyLinkedListTest, PrintNonEmptyList) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output == "10 20 ");
}

TEST(DoublyLinkedListTest, DestructorCleansUp) {
    DoublyLinkedList<int>* list = new DoublyLinkedList<int>();
    for (int i = 0; i < 10; ++i) {
        list->push_back(i);
    }
    delete list; // Проверяем что нет утечек памяти
}

TEST(DoublyLinkedListTest, MultipleRemoveOperations) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(10);
    list.push_back(30);
    
    EXPECT_TRUE(list.remove_first(10));
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_TRUE(list.has_item(10));
    
    EXPECT_TRUE(list.remove_first(10));
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_FALSE(list.has_item(10));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}