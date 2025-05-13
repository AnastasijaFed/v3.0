//
// Created by Anastasija Fedorenko on 2025-03-28.
//

#ifndef STUDENTCLASS_H
#define STUDENTCLASS_H
#include <string>
#include <vector>
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



            const vector<double> getGrades()const{return grades;}
            const double getExamGrades()const{return exam_grade;}
            const void setExamGrades(const double grade){this->exam_grade = grade;}
            const void setGrades(const vector<double> grades){this->grades = grades;}
            void clearGrades(){this->grades.clear();}
            const void setFinalGrade(const double finalGrade){this->final_grade = finalGrade;}
            const double getFinalGrade()const{return final_grade;}
            vector<StudentClass> addStudentsObjects(vector<StudentClass> students);
            double averageClass(StudentClass &student);
            double medianClass(StudentClass &student);
          double calculateFinalGradesMedianClass(StudentClass &student);
            void calculateFinalGradesAverageClass(StudentClass &student);
          void printStudentListClass(vector<StudentClass> &students);
            void generateGradesClass(vector<StudentClass> &students);
        vector<string> loadFromFileClass(const string &filename);
      void writeStudentsToFile(const vector<StudentClass>& students, const string& filename);
          vector<StudentClass> readStudentsFileClass(const string &filename);
        vector<StudentClass> generateRandomStudentsClass(int count);
          vector<StudentClass> testClass();
        static bool compareByNameClass(StudentClass a, StudentClass b);
        static bool compareBySurnameClass(StudentClass a, StudentClass b);
        bool compareByAverageClass(StudentClass a, StudentClass b);
        vector<StudentClass> sortByNameClass(vector<StudentClass> students);
        vector<StudentClass> sortBySurnameClass(vector<StudentClass> students);
        vector<StudentClass> sortByAverageClass(vector<StudentClass> students);
        void logDuration(const string& message, const std::chrono::high_resolution_clock::time_point& start, const std::chrono::high_resolution_clock::time_point& stop);
        void generateStudentsFileClass(int numberOfStudents);
        void sortStudentsInFileClass(vector<StudentClass>& students,int numberOfStudents);
        void strategyTwoVectorClass(vector<StudentClass>& students, vector<StudentClass>& vargsiukai, int num);
        void strategyThreeVector(vector<StudentClass>& students, vector<StudentClass>& vargsiukai, int num);



          //default konstruktorius
      StudentClass() : Human(), grades{}, exam_grade(0), final_grade(0) {}

      void printInfo() override {
          cout << "Vardas: " << getName() << ", Pavarde: " << getSurname()
               << ", Gal. pazymys: " << fixed << setprecision(2) << getFinalGrade() << endl;
      }

            //konstruktorius
      StudentClass(string name, string surname, vector<double> grades, double exam_grade, double finalGrade)
          : Human(name, surname),
            grades(grades),
            exam_grade(exam_grade),
            final_grade(finalGrade) {}


          //copy konstruktorius
      StudentClass(const StudentClass &student)
    : Human(student.getName(), student.getSurname()),
      grades(student.grades),
      exam_grade(student.exam_grade),
      final_grade(student.final_grade) {}
  //copy asignment operator
      StudentClass& operator=(const StudentClass &student) {
        if (this == &student) return *this;
        Human::setName(student.getName());
        Human::setSurname(student.getSurname());
        grades = student.grades;
        exam_grade = student.exam_grade;
        final_grade = student.final_grade;
        return *this;
      }
      //move konstruktorius
      StudentClass(StudentClass&& student) noexcept
        : Human(std::move(student)),
          grades(std::move(student.grades)),
          exam_grade(student.exam_grade),
          final_grade(student.final_grade) {
        student.exam_grade = 0.0;
        student.final_grade = 0.0;
        student.grades.clear();
        student.name.clear();
        student.surname.clear();
      }

      //move assignment operatorius
      StudentClass& operator=(StudentClass&& student) noexcept {
        if (this == &student) return *this;
        Human::operator=(std::move(student));
        grades = std::move(student.grades);
        exam_grade = student.exam_grade;
        final_grade = student.final_grade;
        student.exam_grade = 0;
        student.final_grade = 0;
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
            vector<double> grades;
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
            name.clear();
            surname.clear();
            grades.clear();
            exam_grade = 0;
            final_grade = 0;

          }


       private:
        string name;
        string surname;
        ::vector<double> grades;
        double exam_grade;
        mutable double final_grade;
    };



#endif //STUDENTCLASS_H
