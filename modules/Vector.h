//
// Created by Anastasija Fedorenko on 2025-05-11.
//

#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <stdexcept>
#include <utility>     // for std::move
#include <algorithm>
#include <memory>

using namespace std;

template<class T>, typename Allocator = allocator<T>>

class Vector {

private:
    T* vector;   // pointer to first data element
    size_t capacity;   // current memory capacity
    size_t curr_idx;   // current vector size (same as numel)
    Allocator alloc;



public:

  //default konstruktorius
    Vector(){
        vector = nullptr;
        capacity = 0;
        curr_idx = 0;
        alloc = Allocator();
      }

    Vector(size_t count, const T& value){
      vector = alloc.allocate(count);
      capacity = count;
      curr_idx = count;
      for (size_t i = 0; i < count; ++i) {
        alloc.construct(vector + i, value);
      }
      }

    ~Vector(){
      for (size_t i = 0; i < curr_idx; ++i) {
        alloc.destroy(vector + i);
      }
      if (vector) {
        alloc.deallocate(vector, capacity); // free memory
      }
      }

    T& operator[](const size_t index){
      return vector[index];
        }
//copy assignment operator
  vectorClass& operator=(const vectorClass& other) {
      if (this != &other) {
        for (size_t i = 0; i < curr_idx; ++i)
          alloc.destroy(vector + i);
        if (vector)
          alloc.deallocate(vector, capacity);

        capacity = other.capacity;
        curr_idx = other.curr_idx;
        vector = alloc.allocate(capacity);
        for (size_t i = 0; i < curr_idx; ++i)
          alloc.construct(vector + i, other.vector[i]);
      }
      return *this;
    }
//move assignment operator
  vectorClass& operator=(vectorClass&& other) noexcept {
      if (this != &other) {
        for (size_t i = 0; i < curr_idx; ++i)
          alloc.destroy(vector + i);
        if (vector)
          alloc.deallocate(vector, capacity);

        vector = other.vector;
        capacity = other.capacity;
        curr_idx = other.curr_idx;
        other.vector = nullptr;
        other.capacity = 0;
        other.curr_idx = 0;
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
  //grąžina vektoriaus dydį
  size_t size() const noexcept {
      return crr_idx;
    }

  //padidina vektoriaus capacity
  void reserve(size_t new_cap) {
      if (new_cap <= capacity) return;

      // Alokuojam naują dalį atminties
      T* new_data = alloc.allocate(new_cap);

      // perkeliam egzistuojančius elementus į rezervuotą atmintį
      for (size_t i = 0; i < curr_idx; ++i) {
        alloc.construct(new_data + i, std::move_if_noexcept(vector[i]));
        alloc.destroy(vector + i);
      }

      // Dealokuojam seną atmintį
      if (vector) {
        alloc.deallocate(vector, capacity);
      }


      vector = new_data;
      capacity = new_cap;
    }

  //grąžina vektoriaus capacity
  size_t capacity() const noexcept {
      return capacity;
    }




};



#endif //VECTORCLASS_H
