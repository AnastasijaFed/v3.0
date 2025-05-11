//
// Created by Anastasija Fedorenko on 2025-05-11.
//

#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <stdexcept>
#include <utility>     // for std::move
#include <algorithm>
using namespace std;

template<class T> class Vector {

private:
    T* vector;   // pointer to first data element
    size_t capacity;   // current memory capacity
    size_t curr_idx;   // current vector size (same as numel)



public:

  //default konstruktorius
    Vector(){
        vector = nullptr;
        capacity = 0;
        curr_idx = 0;
      }

    Vector(size_t count, const T& value){
      data = new T[count];
      fill(data, data + count, value);
      capacity = count;
      curr_idx = count;
      }

    ~Vector(){
      delete[] vector;
      }

    T& operator[](const size_t index){
      return vector[index];
        }

  vectorClass& operator=(const vectorClass& other) {
      if (this != &other) {
        delete[] vector;

        curr_idx = other.curr_idx;
        capacity = other.capacity;
        vector = new T[capacity];
        std::copy(other.vector, other.vector + curr_idx, vector);  // deep copy
      }
      return *this;
    }

  vectorClass& operator=(vectorClass&& other) noexcept {
      if (this != &other) {
        delete[] vector;

        vector = other.vector;
        curr_idx = other.curr_idx;
        capacity = other.capacity;

        other.vector = nullptr;
        other.curr_idx = 0;
        other.capacity = 0;
      }
      return *this;
    }
    //pakeičia dabartines vektoriaus reikšmes į kopijas reikšmių value count kartų
    void assign(size_t count, const T& value){
      if (count > capacity) {
        delete[] vector;
        vector = new T[count];
        capacity = count;
      }
      for (size_t i = 0; i < count; ++i) {
        vector[i] = value;
      }

      curr_idx = count;
    }


};



#endif //VECTORCLASS_H
