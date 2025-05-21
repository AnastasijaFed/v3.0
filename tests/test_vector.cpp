//
// Created by Anastasija Fedorenko on 20/05/2025.
//
#include <gtest/gtest.h>
#include "Vector.h"  // Replace with actual path to your class

TEST(VectorTest, DefaultConstructor) {
    Vector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, InitializerListConstructor) {
    Vector<int> vec = {1, 2, 3};
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, CopyConstructor) {
    Vector<int> vec1 = {1, 2, 3};
    Vector<int> vec2 = vec1;
    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
    EXPECT_EQ(vec2[2], 3);
}

TEST(VectorTest, MoveConstructor) {
    Vector<int> vec1 = {1, 2, 3};
    Vector<int> vec2 = std::move(vec1);
    EXPECT_EQ(vec2.size(), 3);
}

TEST(VectorTest, CopyAssignment) {
    Vector<int> vec1 = {4, 5, 6};
    Vector<int> vec2;
    vec2 = vec1;
    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec2[1], 5);
}

TEST(VectorTest, MoveAssignment) {
    Vector<int> vec1 = {4, 5, 6};
    Vector<int> vec2;
    vec2 = std::move(vec1);
    EXPECT_EQ(vec2.size(), 3);
}

TEST(VectorTest, PushBack) {
    Vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[1], 20);
}

TEST(VectorTest, PopBack) {
    Vector<int> vec = {1, 2, 3};
    vec.pop_back();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.back(), 2);
}

TEST(VectorTest, AtBoundsCheck) {
    Vector<int> vec = {10, 20};
    EXPECT_EQ(vec.at(1), 20);
    EXPECT_THROW(vec.at(2), std::out_of_range);
}

TEST(VectorTest, ResizeSmaller) {
    Vector<int> vec = {1, 2, 3};
    vec.resize(2);
    EXPECT_EQ(vec.size(), 2);
}

TEST(VectorTest, ResizeLargerWithDefault) {
    Vector<int> vec = {1, 2};
    vec.resize(4);
    EXPECT_EQ(vec.size(), 4);
}

TEST(VectorTest, ResizeWithValue) {
    Vector<int> vec = {1};
    vec.resize(3, 7);
    EXPECT_EQ(vec[2], 7);
}

TEST(VectorTest, Clear) {
    Vector<int> vec = {1, 2, 3};
    vec.clear();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, InsertAtMiddle) {
    Vector<int> vec = {1, 3};
    vec.insert(vec.begin() + 1, 2);
    EXPECT_EQ(vec[1], 2);
}

TEST(VectorTest, EraseSingle) {
    Vector<int> vec = {1, 2, 3};
    vec.erase(vec.begin() + 1);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[1], 3);
}

TEST(VectorTest, EmplaceBack) {
    Vector<std::pair<int, int>> vec;
    vec.emplace_back(1, 2);
    EXPECT_EQ(vec[0].first, 1);
    EXPECT_EQ(vec[0].second, 2);
}

TEST(VectorTest, AssignCountValue) {
    Vector<int> vec;
    vec.assign(4, 5);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[2], 5);
}

TEST(VectorTest, AssignRange) {
    std::vector<int> stdvec = {7, 8, 9};
    Vector<int> vec;
    vec.assign_range(stdvec.begin(), stdvec.end());
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[1], 8);
}


TEST(VectorTest, IteratorFunctionality) {
    Vector<int> vec = {10, 20, 30};
    int sum = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 60);
}
