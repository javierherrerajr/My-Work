#include "gtest/gtest.h"
#include "../include/Triangle.h"
using shapes::Triangle;


TEST(TriangleTests, testPerimeter) {
    Triangle *aTriangle = new Triangle(5,5,4);
    EXPECT_EQ (aTriangle->getPerimeter(),14);
}

TEST(TriangleTests, testArea) {
    Triangle *aTriangle = new Triangle(3,3,3);
    EXPECT_EQ (aTriangle->getArea(),27);
}

TEST(TriangleTests, testKind) {
    Triangle *aTriangle = new Triangle(3,3,3);
    EXPECT_EQ (aTriangle->getKind(),shapes::Triangle::Kind::EQUILATERAL);
}

TEST(TriangleTests, testTermination) {
    EXPECT_DEATH (Triangle *aTriangle = new Triangle(3,4,5), "First side is not the longest");
}

TEST(TriangleTests, testPerimeter2) {
    Triangle *aTriangle = new Triangle(3,3,3);
    EXPECT_EQ (aTriangle->getPerimeter(),9);
}

TEST(TriangleTests, testException) {
    EXPECT_NO_THROW (Triangle *aTriangle = new Triangle(5,4,3));
}

TEST(TriangleTests, testKind2) {
    Triangle *aTriangle = new Triangle(5,5,3);
    EXPECT_EQ(aTriangle->getKind(),shapes::Triangle::Kind::ISOSCELES);
}

TEST(TriangleTests, testTermination2) {
    EXPECT_DEATH(Triangle *aTriangle = new Triangle(5,2,2), "Does not satisfy triangle inequality");
}