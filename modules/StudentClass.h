//
// Created by Anastasija Fedorenko on 2025-03-28.
//

#ifndef STUDENTCLASS_H
#define STUDENTCLASS_H
#include <string>
#include "Vector.h"
#include <iostream>
#include <numeric>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Human.h"
using namespace std;

    class StudentClass : public Human {
        public:



            Vector<double> getGrades()const {return grades;}
            double getExamGrades()const{return exam_grade;}
            void setExamGrades(const double grade){this->exam_grade = grade;}
            void setGrades(const Vector<double> grades){this->grades = grades;}
            void clearGrades(){this->grades.clear();}
            void setFinalGrade(const double finalGrade){this->final_grade = finalGrade;}
            double getFinalGrade()const{return final_grade;}
             Vector<StudentClass> addStudentsObjects(::Vector<StudentClass> students);
            static double averageClass(const StudentClass &student);
            double medianClass(StudentClass &student);
          double calculateFinalGradesMedianClass(StudentClass &student);
            void calculateFinalGradesAverageClass(StudentClass &student);
          void printStudentListClass(Vector<StudentClass> &students);
            void generateGradesClass(Vector<StudentClass> &students);
        Vector<string> loadFromFileClass(const string &filename);
      void writeStudentsToFile(const Vector<StudentClass>& students, const string& filename);
          static Vector<StudentClass> readStudentsFileClass(const string &filename);
        Vector<StudentClass> generateRandomStudentsClass(int count);
          Vector<StudentClass> testClass();
        bool compareByNameClass(const StudentClass& a, const StudentClass& b);
        bool compareBySurnameClass(const StudentClass& a, const StudentClass& b);
        bool compareByAverageClass(const StudentClass& a, const StudentClass& b);
        Vector<StudentClass> sortByNameClass(Vector<StudentClass>& students);
        Vector<StudentClass> sortBySurnameClass(Vector<StudentClass>& students);
        Vector<StudentClass> sortByAverageClass(Vector<StudentClass>& students);
        void logDuration(const string& message, const std::chrono::high_resolution_clock::time_point& start, const std::chrono::high_resolution_clock::time_point& stop);
        void generateStudentsFileClass(int numberOfStudents);
        void sortStudentsInFileClass(Vector<StudentClass>& students,int numberOfStudents);
        void strategyTwoVectorClass(Vector<StudentClass>& students, Vector<StudentClass>& vargsiukai, int num);
        void strategyThreeVector(Vector<StudentClass>& students, Vector<StudentClass>& vargsiukai, int num);



          //default konstruktorius
      StudentClass() : Human(), grades{}, exam_grade(0), final_grade(0) {}

      void printInfo() override {
          cout << "Vardas: " << getName() << ", Pavarde: " << getSurname()
               << ", Gal. pazymys: " << fixed << setprecision(2) << getFinalGrade() << endl;
      }


    // Constructor
    StudentClass(std::string name, std::string surname, Vector<double> grades,
                 double exam_grade, double finalGrade)
        : Human(std::move(name), std::move(surname)),
          grades(std::move(grades)),
          exam_grade(exam_grade),
          final_grade(finalGrade) {}

    // Copy constructor
    StudentClass(const StudentClass& other)
        : Human(other.getName(), other.getSurname()),
          grades(other.grades),
          exam_grade(other.exam_grade),
          final_grade(other.final_grade) {

          }

    // Copy assignment
    StudentClass& operator=(const StudentClass& other) {
        if (this != &other) {
            setName(other.getName());
            setSurname(other.getSurname());
            grades = other.grades;
            exam_grade = other.exam_grade;
            final_grade = other.final_grade;
        }
        return *this;
    }

    // Move constructor
 StudentClass(StudentClass&& student) noexcept
    : Human(std::move(student.name), std::move(student.surname)),
      grades(std::move(student.grades)),
      exam_grade(student.exam_grade),
      final_grade(student.final_grade) {
    student.exam_grade = 0.0;
    student.final_grade = 0.0;
}

    // Move assignment
    StudentClass& operator=(StudentClass&& student) noexcept {
    if (this != &student) {
        Human::operator=(std::move(student));
        grades = std::move(student.grades);
        exam_grade = student.exam_grade;
        final_grade = student.final_grade;

        student.exam_grade = 0;
        student.final_grade = 0;
        // NO clearing name/surname
    }
    return *this;
}


      friend ostream& operator<<(ostream& os, const StudentClass& student) {

            os << left
               << setw(15) << student.getSurname()
               << setw(15) << student.getName()
               << right
               << setw(10) << fixed << setprecision(2) << student.getFinalGrade();
            return os;
          }

      friend istream& operator>>(istream& is, StudentClass& student) {
            student = StudentClass();

            string line;
            if (!getline(is >> ws, line)) return is;

            istringstream iss(line);

            string namePart, surnamePart;
            if (!(iss >> namePart >> surnamePart)) return is;

            student.setName(namePart);
            student.setSurname(surnamePart);

            // Read grades
            Vector<double> grades;
            double grade;
            while (iss >> grade) {
              grades.push_back(grade);
            }

            if (!grades.empty()) {
              student.setExamGrades(grades.back());
              grades.pop_back();
              student.setGrades(grades);
              student.calculateFinalGradesAverageClass(student);
            }

            return is;
          }
      ~StudentClass() {
    exam_grade = 0;
    final_grade = 0;
}


       private:
       Vector<double> grades;
        double exam_grade;
        mutable double final_grade;
    };



#endif //STUDENTCLASS_H
