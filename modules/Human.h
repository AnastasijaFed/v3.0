//
// Created by Anastasija Fedorenko on 2025-04-21.
//

#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <iostream>
using namespace std;
class Human {
protected:
    string name;
    string surname;

public:
    Human() = default;
    Human(string name, string surname);
    virtual ~Human() =default;

    virtual void printInfo() = 0;

    Human(Human&& student) noexcept : name(std::move(student.name)), surname(std::move(student.surname)) {}

    Human& operator=(Human&& other) noexcept {
        if (this == &other) return *this;
        name = std::move(other.name);
        surname = std::move(other.surname);
        return *this;
    }


    string getName()const{return name;}
    string getSurname()const{return surname;}
    const void setName(const string name){this->name = name;}
    const void setSurname(const string surname){this->surname = surname;}
};

#endif