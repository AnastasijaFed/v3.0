

#ifndef STUDENT_H
#define STUDENT_H

//#include <string>
#include <vector>
#include <iostream>
#include <numeric>
#include <iomanip>
#include <cstdint>

struct Student {
    std::string name;
    std::string surname;
    std::vector<uint8_t> grades;
    uint8_t exam_grade;
    mutable double final_grade;

};



#endif //STUDENT_H
