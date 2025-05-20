#include <gtest/gtest.h>
#include "../modules/StudentClass.h"

class StudentClassTest : public ::testing::Test {
protected:
    StudentClass student;

    void SetUp() override {
        student.setName("Jonas");
        student.setSurname("Jonaitis");
        student.setGrades({8, 9, 10});
        student.setExamGrades(9);
    }
};

TEST_F(StudentClassTest, AverageCalculation) {
    double avg = student.StudentClass::averageClass(student);
    EXPECT_DOUBLE_EQ(avg, (8 + 9 + 10) / 3.0);
}


TEST_F(StudentClassTest, FinalGradeFromAverage) {
    student.StudentClass::calculateFinalGradesAverageClass(student);
    EXPECT_DOUBLE_EQ(student.getFinalGrade(), (9.0 * 0.6 + (8 + 9 + 10) / 3.0 * 0.4));
}


TEST(SortingTest, SortByAverage) {
    StudentClass a, b;
    a.setGrades({10, 10});
    a.setExamGrades(10);
    a.StudentClass::calculateFinalGradesAverageClass(a);

    b.setGrades({5, 5});
    b.setExamGrades(5);
    b. StudentClass::calculateFinalGradesAverageClass(b);

    Vector<StudentClass> list = {a, b};
    Vector<StudentClass> sorted = a.sortByAverageClass(list);
    EXPECT_EQ(sorted[0].getFinalGrade(), b.getFinalGrade());
}

