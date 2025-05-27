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
   	const string& getName() const {return name;}
    const string& getSurname() const {return surname;}
    void setName(const string& name) { this->name = name; }
	void setSurname(const string& surname) { this->surname = surname; }
    Human(){
      name = "";
      surname = "";
      }
    Human(string name, string surname);
    virtual ~Human() =default;

    virtual void printInfo() const = 0;

    Human(Human&& student) noexcept : name(std::move(student.name)), surname(std::move(student.surname)) {}

    Human(const Human& other) : name(other.name), surname(other.surname) {}


    Human& operator=(const Human& other) {
        if (this == &other) return *this;
        name = other.name;
        surname = other.surname;
        return *this;
    }
    Human& operator=(Human&& other) noexcept {
        if (this == &other) return *this;
        name = std::move(other.name);
        surname = std::move(other.surname);
        return *this;
    }



};

#endif