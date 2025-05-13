//
// Created by Anastasija Fedorenko on 2025-05-11.
//
#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>     // for std::move
#include <algorithm>
#include <memory>

using namespace std;

template<class T, typename Allocator = allocator<T>>

class Vector {

private:
    T* vector;   // pointer to first data element
    size_t cpct;   // current memory capacity
    size_t curr_idx;   // current vector size (same as numel)
    Allocator alloc;



public:
//MEMBER TYPE DEFINITIONS
  using value_type             = T;
  using allocator_type         = Allocator;
  using size_type              = size_t;
  using difference_type        = ptrdiff_t;
  using reference              = value_type&;
  using const_reference        = const value_type&;
  using pointer                = typename allocator_traits<Allocator>::pointer;
  using const_pointer          = typename allocator_traits<Allocator>::const_pointer;
  using iterator               = pointer;
  using const_iterator         = const_pointer;
  using reverse_iterator       = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;


  //MEMBER FUNCTIONS

  //default konstruktorius
    Vector(){
        vector = nullptr;
        cpct = 0;
        curr_idx = 0;
        alloc = Allocator();
      }
  //konstruktorius
    Vector(size_t count, const T& value){
      vector = alloc.allocate(count);
      cpct = count;
      curr_idx = count;
      for (size_t i = 0; i < count; ++i) {
        alloc.construct(vector + i, value);
      }
      }
  //destruktorius
    ~Vector(){
      for (size_t i = 0; i < curr_idx; ++i) {
        destroy_at(vector + i);
      }
      if (vector) {
        alloc.deallocate(vector, cpct); // free memory
      }
      }
  //copy assignment operator
  Vector& operator=(const Vector& other) {
      if (this != &other) {
        for (size_t i = 0; i < curr_idx; ++i)
          destroy_at(vector + i);
        if (vector)
          alloc.deallocate(vector, cpct);

        cpct = other.cpct;
        curr_idx = other.curr_idx;
        vector = alloc.allocate(cpct);
        for (size_t i = 0; i < curr_idx; ++i)
          alloc.construct(vector + i, other.vector[i]);
      }
      return *this;
    }
  //move assignment operator
  Vector& operator=(Vector&& other) noexcept {
      if (this != &other) {
        for (size_t i = 0; i < curr_idx; ++i)
          alloc.destroy(vector + i);
        if (vector)
          alloc.deallocate(vector, cpct);

        vector = other.vector;
        cpct = other.cpct;
        curr_idx = other.curr_idx;
        other.vector = nullptr;
        other.cpct = 0;
        other.curr_idx = 0;
      }
      return *this;
    }
  //pakeičia dabartines vektoriaus reikšmes į kopijas reikšmių value count kartų
  void assign(size_t count, const T& value){
      if (count > cpct) {
        delete[] vector;
        vector = new T[count];
        cpct = count;
      }
      for (size_t i = 0; i < count; ++i) {
        vector[i] = value;
      }

      curr_idx = count;
    }

  //pakeičia dabartines vektoriaus reikšmes į kopiją range reikšmių value count kartų
  template<typename InputIt>
void assign_range(InputIt first, InputIt last) {
      size_type count = std::distance(first, last);

      // paašalinam dabartinius elementus
      for (size_type i = 0; i < curr_idx; ++i) {
        std::allocator_traits<Allocator>::destroy(alloc, vector + i);
      }

      if (count > cpct) {
        if (vector) {
          alloc.deallocate(vector, cpct);
        }
        vector = alloc.allocate(count);
        cpct = count;
      }

      // sukonstruojam naujus elementus
      size_type i = 0;
      for (InputIt it = first; it != last; ++it, ++i) {
        std::allocator_traits<Allocator>::construct(alloc, vector + i, *it);
      }

      curr_idx = count;
    }
//grąžina allocator'ių
  allocator_type get_allocator() const noexcept {
      return alloc;
    }

    //ELEMENT ACCESS

  //leidžia pasiekti tam tikrą elementą tikrinant ribas
  T& at(size_t index) {
      if (index >= curr_idx) throw std::out_of_range("Išeina už vektoriaus ribų");
      return vector[index];
    }

    //leidžia pasiekti tam tikrą elementą netikrinant ribų
    T& operator[](const size_t index){
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
      return vector[curr_idx - 1];
    }
//Pointer to the underlying element storage
  T* data() noexcept { return vector; }

  //Iteratoriai

  iterator begin() noexcept { return vector; }
  const_iterator cbegin() const noexcept { return vector; }
  iterator end() noexcept { return vector + curr_idx; }
  const_iterator cend() const noexcept { return vector + curr_idx; }

 //CAPACITY
//patikrina ar vektorius yra tusčias
  bool empty() const noexcept {
      return curr_idx == 0;
    }
  //grąžina vektoriaus dydį
  size_t size() const noexcept {
      return curr_idx;
    }
    //grąžina didžiausia galimą elementų skaičių
  size_type max_size() const noexcept {
      return allocator_traits<Allocator>::max_size(alloc);
    }

  //padidina vektoriaus capacity
  void reserve(size_t new_cap) {
      if (new_cap <= cpct) return;

      // Alokuojam naują dalį atminties
      T* new_data = alloc.allocate(new_cap);
      // perkeliam egzistuojančius elementus į rezervuotą atmintį
      for (size_t i = 0; i < curr_idx; ++i) {
        std::allocator_traits<Allocator>::construct(alloc, new_data + i, std::move_if_noexcept(vector[i]));
        destroy_at(vector + i);
      }
      // Dealokuojam seną atmintį
      if (vector) {
        alloc.deallocate(vector, cpct);
      }
      vector = new_data;
      cpct = new_cap;
    }

  //grąžina vektoriaus capacity
  size_t capacity() const noexcept {
      return cpct;
    }
 //atlaisvina nenaudojamą atmintį
  void shrink_to_fit() {
      if (cpct > curr_idx) {
        T* new_data = alloc.allocate(curr_idx);

        // perkeliam egzistuojančius elementus į naują atminties bloką
        for (size_t i = 0; i < curr_idx; ++i) {
          std::allocator_traits<Allocator>::construct(alloc, new_data + i, std::move_if_noexcept(vector[i]));
          std::allocator_traits<Allocator>::destroy(alloc, vector + i);
        }

        // dealokuoti seną atmintį
        if (vector) {
          alloc.deallocate(vector, cpct);
        }

        vector = new_data;
        cpct = curr_idx;
      }
    }

//MODIFIERS

  //ištrina visus elementus
  void clear() noexcept {
      for (size_t i = 0; i < curr_idx; ++i) {
        allocator_traits<Allocator>::destroy(alloc, vector + i);
      }
      curr_idx = 0;
    }
  //įterpia elementą į nurodytą poziciją
  iterator insert(const_iterator pos, const T& value) {
      size_t index = pos - vector;

   //ar uztenka atminties
      if (curr_idx >= cpct) {
        size_t new_capacity = (cpct == 0) ? 1 : cpct * 2;
        T* new_data = alloc.allocate(new_capacity);

        //perkeliam pries iterpimo vieta
        for (size_t i = 0; i < index; ++i) {
          std::allocator_traits<Allocator>::construct(alloc, new_data + i, std::move_if_noexcept(vector[i]));
          std::allocator_traits<Allocator>::destroy(alloc, vector + i);
        }

        // iterpiam nauja elementa
        std::allocator_traits<Allocator>::construct(alloc, new_data + index, value);

        // perkeliam likusius elementus po iterpimo
        for (size_t i = index; i < curr_idx; ++i) {
          std::allocator_traits<Allocator>::construct(alloc, new_data + i + 1, std::move_if_noexcept(vector[i]));
          std::allocator_traits<Allocator>::destroy(alloc, vector + i);
        }

        if (vector) alloc.deallocate(vector, cpct);
        vector = new_data;
        cpct = new_capacity;
      } else {
        //perkeliam reiksmes i desine
        for (size_t i = curr_idx; i > index; --i) {
          std::allocator_traits<Allocator>::construct(alloc, vector + i, std::move_if_noexcept(vector[i - 1]));
          std::allocator_traits<Allocator>::destroy(alloc, vector + i - 1);
        }
        std::allocator_traits<Allocator>::construct(alloc, vector + index, value);
      }

      ++curr_idx;
      return vector + index;
    }
//leidžia įterpti bet kokį konteinerį į Vector
  template<typename InputIt>
void insert_range(T* pos, InputIt first, InputIt last) {
      size_t index = pos - vector;
      size_t count = distance(first, last);

      if (curr_idx + count > cpct) {
        // Not enough capacity, reallocate
        size_t new_cpct = std::max(cpct * 2, curr_idx + count);
        T* new_data = alloc.allocate(new_cpct);

        // Move elements before insertion point
        for (size_t i = 0; i < index; ++i) {
          std::allocator_traits<Allocator>::construct(alloc, new_data + i, std::move_if_noexcept(vector[i]));
          std::allocator_traits<Allocator>::destroy(alloc, vector + i);
        }

        // iterpiam nauja konteineri
        size_t insert_i = index;
        for (InputIt it = first; it != last; ++it, ++insert_i) {
          std::allocator_traits<Allocator>::construct(alloc, new_data + insert_i, *it);
        }

        // perkeliam visa likuti
        for (size_t i = index; i < curr_idx; ++i, ++insert_i) {
          std::allocator_traits<Allocator>::construct(alloc, new_data + insert_i, std::move_if_noexcept(vector[i]));
          std::allocator_traits<Allocator>::destroy(alloc, vector + i);
        }

        if (vector) alloc.deallocate(vector, cpct);
        vector = new_data;
        cpct = new_cpct;
      } else {
        // perkeliam elementus i desine
        for (size_t i = curr_idx + count - 1; i >= index + count && i < SIZE_MAX; --i) {
          std::allocator_traits<Allocator>::construct(alloc, vector + i, std::move_if_noexcept(vector[i - count]));
          std::allocator_traits<Allocator>::destroy(alloc, vector + i - count);
        }

        // iterpiam range i jo vieta
        size_t insert_i = index;
        for (InputIt it = first; it != last; ++it, ++insert_i) {
          std::allocator_traits<Allocator>::construct(alloc, vector + insert_i, *it);
        }
      }

      curr_idx += count;
    }

//įterpia elementą į tam tikrą poziciją tiesiogiai iškviesdamas konstruktorių
   template<typename... Args>
iterator emplace(const_iterator pos, Args&&... args) {
    size_t index = pos - vector;

    if (curr_idx >= cpct) {
        size_t new_capacity = (cpct == 0) ? 1 : cpct * 2;
        T* new_data = alloc.allocate(new_capacity);


        for (size_t i = 0; i < index; ++i) {
            allocator_traits<Allocator>::construct(alloc, new_data + i, std::move_if_noexcept(vector[i]));
            allocator_traits<Allocator>::destroy(alloc, vector + i);
        }
		//konstruojam naują objektą
        // Naudojam forward, kad išsaugotumem value category (pvz. move paverčia arg į rvalue)
        allocator_traits<Allocator>::construct(alloc, new_data + index, forward<Args>(args)...);


        for (size_t i = index; i < curr_idx; ++i) {
            allocator_traits<Allocator>::construct(alloc, new_data + i + 1, move_if_noexcept(vector[i]));
            allocator_traits<Allocator>::destroy(alloc, vector + i);
        }

        if (vector) alloc.deallocate(vector, cpct);
        vector = new_data;
        cpct = new_capacity;
    } else {

        for (size_t i = curr_idx; i > index; --i) {
            allocator_traits<Allocator>::construct(alloc, vector + i, std::move_if_noexcept(vector[i - 1]));
            allocator_traits<Allocator>::destroy(alloc, vector + i - 1);
        }

        // Naudojam forward, kad išsaugotumem value category (pvz. move paverčia arg į rvalue)
       allocator_traits<Allocator>::construct(alloc, vector + index, forward<Args>(args)...);
    }

    ++curr_idx;
    return vector + index;
}


  //ištrina elementą nurodytoje pozicijoje
  T* erase(T* pos) {
      size_t index = pos - vector;
      allocator_traits<Allocator>::destroy(alloc, vector + index);


      for (size_t i = index + 1; i < curr_idx; ++i) {
        std::allocator_traits<Allocator>::construct(alloc, vector + i - 1, std::move_if_noexcept(vector[i]));
        std::allocator_traits<Allocator>::destroy(alloc, vector + i);
      }

      --curr_idx;
      return vector + index;
    }

  //ištrina elementus nurodytoje atkarpoje
  T* erase(T* first, T* last) {
      size_t start = first - vector;
      size_t end = last - vector;
      size_t count = end - start;


      for (size_t i = start; i < end; ++i) {
        std::allocator_traits<Allocator>::destroy(alloc, vector + i);
      }

      for (size_t i = end; i < curr_idx; ++i) {
        std::allocator_traits<Allocator>::construct(alloc, vector + i - count, std::move_if_noexcept(vector[i]));
        std::allocator_traits<Allocator>::destroy(alloc, vector + i);
      }

      curr_idx -=  count;
      return vector + start;
    }

   //prideda elementą į vektoriaus pabaigą
  void push_back(const T& value) {

      if (curr_idx == cpct) {
        reserve(cpct == 0 ? 1 : cpct * 2);
      }
      allocator_traits<Allocator>::construct(alloc, vector + curr_idx, value);
      ++curr_idx;
    }

    //įterpia objektą į vektoriaus pabaigą iš karto naudojant konstruktorių
    template <typename... Args>
void emplace_back(Args&&... args) {

    if (curr_idx == cpct) {
        reserve(cpct == 0 ? 1 : cpct * 2);
    }

    std::allocator_traits<Allocator>::construct(alloc, vector + curr_idx, forward<Args>(args)...);

    ++curr_idx;
}














};



//VECTORCLASS_H
