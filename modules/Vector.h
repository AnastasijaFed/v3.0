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
//copy assignment operator
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
//move assignment operator
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
//leidžia pasiekti tam tikrą elementą tikrinant ribas
  T& at(size_t index) {
      if (index >= curr_idx) throw std::out_of_range("Išeina už vektoriaus ribų");
      return vector[index];
    }
//leidžia pasiekti pirmąjį elementą
  T& front() {
      if (curr_idx == 0) {
        throw std::out_of_range("Vektorius tusčias");
      }
      return vector[0];
    }
//leidžia pasiekti paskutinįjį elementą
  T& back() {
      if (curr_idx == 0) {
        throw std::out_of_range("Vektorius tusčias");
      }
      return vector[cur_idx - 1];
    }
//Pointer to the underlying element storage
  T* data() noexcept { return vector; }

  //Iteratorius į vektoriaus pradžią
  T* begin() noexcept {
      return vector;
    }
   //Const iteratorius į vektoriaus pradžią
  const T* cbegin() const noexcept {
      return vector;
    }
  //Iteratorius į vektoriaus pabaigą
  T* end() noexcept {
      return vector + curr_idx;
    }
  //Const iteratorius į vektoriaus pabaigą
  const T* cend() const noexcept {
      return vector + curr_idx;
    }
//patikrina ar vektorius yra tusčias
  bool empty() const noexcept {
      return curr_idx == 0;
    }
  bool empty() const noexcept {
      return curr_idx == 0;
    }




};



#endif //VECTORCLASS_H
