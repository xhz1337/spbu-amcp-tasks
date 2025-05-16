#include "vector.hpp"
#include <gtest/gtest.h>

using mmh::Vector;

TEST(VectorTest, ConstructorInitializesEmptyVector) {
    Vector<int> v;
    EXPECT_EQ(v.get_size(), 0);
}

TEST(VectorTest, PushBackIncreasesSize) {
    Vector<int> v;
    v.push_back(10);
    EXPECT_EQ(v.get_size(), 1);
    v.push_back(20);
    EXPECT_EQ(v.get_size(), 2);
}

TEST(VectorTest, HasItemFindsElements) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    
    EXPECT_TRUE(v.has_item(10));
    EXPECT_TRUE(v.has_item(20));
    EXPECT_TRUE(v.has_item(30));
    EXPECT_FALSE(v.has_item(40));
}

TEST(VectorTest, InsertAtPosition) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(30);
    
    EXPECT_TRUE(v.insert(1, 20));
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(20));
}

TEST(VectorTest, InsertAtInvalidPositionFails) {
    Vector<int> v;
    v.push_back(10);
    
    EXPECT_FALSE(v.insert(2, 20));
    EXPECT_EQ(v.get_size(), 1);
}

TEST(VectorTest, RemoveFirstElement) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    
    EXPECT_TRUE(v.remove_first(20));
    EXPECT_EQ(v.get_size(), 2);
    EXPECT_FALSE(v.has_item(20));
}

TEST(VectorTest, RemoveNonExistentElementFails) {
    Vector<int> v;
    v.push_back(10);
    
    EXPECT_FALSE(v.remove_first(20));
    EXPECT_EQ(v.get_size(), 1);
}

TEST(VectorTest, AutoResizeWhenCapacityReached) {
    Vector<int> v;
    const size_t initial_capacity = v.get_size();
    
    for (int i = 0; i < 20; ++i) {
        v.push_back(i);
    }
    
    EXPECT_GT(v.get_size(), initial_capacity);
    EXPECT_EQ(v.get_size(), 20);
}

TEST(VectorTest, InsertCausesResize) {
    Vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    
    EXPECT_TRUE(v.insert(5, 99));
    EXPECT_EQ(v.get_size(), 11);
    EXPECT_TRUE(v.has_item(99));
}

TEST(VectorTest, RemoveLastElement) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    
    EXPECT_TRUE(v.remove_first(20));
    EXPECT_EQ(v.get_size(), 1);
    EXPECT_TRUE(v.has_item(10));
    EXPECT_FALSE(v.has_item(20));
}

TEST(VectorTest, RemoveFirstElementShiftsOthers) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    
    EXPECT_TRUE(v.remove_first(10));
    EXPECT_EQ(v.get_size(), 2);
    EXPECT_TRUE(v.has_item(20));
    EXPECT_TRUE(v.has_item(30));
}

TEST(VectorTest, PrintEmptyVector) {
    Vector<int> v;
    testing::internal::CaptureStdout();
    v.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}

TEST(VectorTest, PrintNonEmptyVector) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    testing::internal::CaptureStdout();
    v.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output == "10 20 ");
}

TEST(VectorTest, InsertAtZeroPosition) {
    Vector<int> v;
    v.push_back(10);
    
    EXPECT_TRUE(v.insert(0, 5));
    EXPECT_EQ(v.get_size(), 2);
    EXPECT_TRUE(v.has_item(5));
}

TEST(VectorTest, InsertAtEndPosition) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    
    EXPECT_TRUE(v.insert(2, 30));
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(30));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}