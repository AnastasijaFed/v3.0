//
// Created by Anastasija Fedorenko on 2025-05-11.
//

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <initializer_list>
#include <memory>
#include <iterator>
#include "StudentClass.h"

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
  using value_type = T;
  using allocator_type = Allocator;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = typename allocator_traits<Allocator>::pointer;
  using const_pointer = typename allocator_traits<Allocator>::const_pointer;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;



  //MEMBER FUNCTIONS

  //default konstruktorius
    Vector() : vector(nullptr), cpct(0), curr_idx(0) {}

  //konstruktorius
    Vector(size_t count, const T& value){
      vector = alloc.allocate(count);
      cpct = count;
      curr_idx = count;
      for (size_t i = 0; i < count; ++i) {
        alloc.construct(vector + i, value);
      }
      }
       // Constructor that accepts an initializer list
     Vector(std::initializer_list<T> init_list) {
        size_t count = init_list.size();
        vector = alloc.allocate(count);  // Allocate memory for the vector
        cpct = count;
        curr_idx = count;
        std::uninitialized_copy(init_list.begin(), init_list.end(), vector);
    }
  //destruktorius
   ~Vector() {
    for (size_t i = 0; i < curr_idx; ++i) {
        std::allocator_traits<Allocator>::destroy(alloc, vector + i);
    }
    if (vector) {
        alloc.deallocate(vector, cpct);
    }
}

      //copy konstruktorius
    Vector(const Vector& other)
    : cpct(other.cpct),
      curr_idx(other.curr_idx),
      alloc(other.alloc) // copy the allocator
{
    vector = allocator_traits<Allocator>::allocate(alloc, cpct);
    for (size_t i = 0; i < curr_idx; ++i) {
        allocator_traits<Allocator>::construct(alloc, vector + i, other.vector[i]);
    }
}

  //copy assignment operator
Vector& operator=(const Vector& other) {
    if (this != &other) {
        for (size_t i = 0; i < curr_idx; ++i) {
            allocator_traits<Allocator>::destroy(alloc, vector + i);
        }
        if (vector) {
            alloc.deallocate(vector, cpct);
        }

        cpct = other.cpct;
        curr_idx = other.curr_idx;
        vector = alloc.allocate(cpct);
        for (size_t i = 0; i < curr_idx; ++i) {
            allocator_traits<Allocator>::construct(alloc, vector + i, other.vector[i]);
        }
    }
    return *this;
}
Vector(Vector&& other) noexcept
    : vector(other.vector), cpct(other.cpct), curr_idx(other.curr_idx), alloc(std::move(other.alloc)) {
    other.vector = nullptr;
    other.cpct = 0;
    other.curr_idx = 0;
}




  //move assignment operator
 Vector& operator=(Vector&& other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < curr_idx; ++i) {
            allocator_traits<Allocator>::destroy(alloc, vector + i);
        }

        if (vector) {
            alloc.deallocate(vector, cpct);
        }

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
    void assign(size_type count, const T& value) {

        for (size_t i = 0; i < curr_idx; ++i) {
            allocator_traits<Allocator>::destroy(alloc, vector + i);
        }

        if (count > cpct) {
            if (vector) {
                alloc.deallocate(vector, cpct);
            }
            vector = alloc.allocate(count);
            cpct = count;
        }
        for (size_t i = 0; i < count; ++i) {
            allocator_traits<Allocator>::construct(alloc, vector + i, value);
        }

        curr_idx = count;
    }

  //pakeičia dabartines vektoriaus reikšmes į kopiją range reikšmių value count kartų
  template<typename InputIt>
void assign_range(InputIt first, InputIt last) {
      size_type count = distance(first, last);

      // paašalinam dabartinius elementus
      for (size_type i = 0; i < curr_idx; ++i) {
        allocator_traits<Allocator>::destroy(alloc, vector + i);
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
        allocator_traits<Allocator>::construct(alloc, vector + i, *it);
      }

      curr_idx = count;
    }
//grąžina allocator'ių
  allocator_type get_allocator() const noexcept {
      return alloc;
    }

    //ELEMENT ACCESS

  //leidžia pasiekti tam tikrą elementą tikrinant ribas
  const T& at(size_t index) {
      if (index >= curr_idx) throw out_of_range("Išeina už vektoriaus ribų");
      return vector[index];
    }

    //leidžia pasiekti tam tikrą elementą netikrinant ribų
    T& operator[](const size_t index){
      return vector[index];
        }

//leidžia pasiekti pirmąjį elementą
  T& front() {
      if (curr_idx == 0) {
        throw out_of_range("Vektorius tusčias");
      }
      return vector[0];
    }
//leidžia pasiekti paskutinįjį elementą
  T& back() {
      if (curr_idx == 0) {
        throw out_of_range("Vektorius tusčias");
      }
      return vector[curr_idx - 1];
    }

  T* data() noexcept { return vector; }

  //Iteratoriai

T* begin() { return (vector != nullptr) ? vector : nullptr; }
T* end() { return (vector != nullptr) ? vector + curr_idx : nullptr; }

const T* begin() const { return (vector != nullptr) ? vector : nullptr; }
const T* end() const { return (vector != nullptr) ? vector + curr_idx : nullptr; }

  const_iterator cbegin() const noexcept { return vector; }
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

    T* new_data = alloc.allocate(new_cap);

    // Move existing elements to new allocation
    for (size_t i = 0; i < curr_idx; ++i) {
    std::allocator_traits<Allocator>::construct(alloc, new_data + i, vector[i]); // copy instead of move
    std::allocator_traits<Allocator>::destroy(alloc, vector + i);
}


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

        for (size_t i = 0; i < curr_idx; ++i) {
          allocator_traits<Allocator>::construct(alloc, new_data + i, move_if_noexcept(vector[i]));
          allocator_traits<Allocator>::destroy(alloc, vector + i);
        }

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
    if (vector) {
        alloc.deallocate(vector, cpct);
        vector = nullptr;
        cpct = 0;
    }
    curr_idx = 0;
}


  //įterpia elementą į nurodytą poziciją
  iterator insert(const_iterator pos, const T& value) {
      size_t index = pos - vector;

      if (curr_idx >= cpct) {
        size_t new_capacity = (cpct == 0) ? 1 : cpct * 2;
        T* new_data = alloc.allocate(new_capacity);

        for (size_t i = 0; i < index; ++i) {
          allocator_traits<Allocator>::construct(alloc, new_data + i, move_if_noexcept(vector[i]));
          allocator_traits<Allocator>::destroy(alloc, vector + i);
        }

        allocator_traits<Allocator>::construct(alloc, new_data + index, value);

        for (size_t i = index; i < curr_idx; ++i) {
          allocator_traits<Allocator>::construct(alloc, new_data + i + 1, move_if_noexcept(vector[i]));
          allocator_traits<Allocator>::destroy(alloc, vector + i);
        }

        if (vector) alloc.deallocate(vector, cpct);
        vector = new_data;
        cpct = new_capacity;
      } else {
        for (size_t i = curr_idx; i > index; --i) {
          allocator_traits<Allocator>::construct(alloc, vector + i, move_if_noexcept(vector[i - 1]));
          allocator_traits<Allocator>::destroy(alloc, vector + i - 1);
        }
        allocator_traits<Allocator>::construct(alloc, vector + index, value);
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
        size_t new_cpct = max(cpct * 2, curr_idx + count);
        T* new_data = alloc.allocate(new_cpct);

        for (size_t i = 0; i < index; ++i) {
          allocator_traits<Allocator>::construct(alloc, new_data + i, move_if_noexcept(vector[i]));
          allocator_traits<Allocator>::destroy(alloc, vector + i);
        }

        size_t insert_i = index;
        for (InputIt it = first; it != last; ++it, ++insert_i) {
         allocator_traits<Allocator>::construct(alloc, new_data + insert_i, *it);
        }

        for (size_t i = index; i < curr_idx; ++i, ++insert_i) {
          allocator_traits<Allocator>::construct(alloc, new_data + insert_i, move_if_noexcept(vector[i]));
          allocator_traits<Allocator>::destroy(alloc, vector + i);
        }

        if (vector) alloc.deallocate(vector, cpct);
        vector = new_data;
        cpct = new_cpct;
      } else {

        for (size_t i = curr_idx + count - 1; i >= index + count && i < SIZE_MAX; --i) {
         allocator_traits<Allocator>::construct(alloc, vector + i, move_if_noexcept(vector[i - count]));
          allocator_traits<Allocator>::destroy(alloc, vector + i - count);
        }

        // iterpiam range i jo vieta
        size_t insert_i = index;
        for (InputIt it = first; it != last; ++it, ++insert_i) {
          allocator_traits<Allocator>::construct(alloc, vector + insert_i, *it);
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
            allocator_traits<Allocator>::construct(alloc, new_data + i, move_if_noexcept(vector[i]));
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
            allocator_traits<Allocator>::construct(alloc, vector + i, move_if_noexcept(vector[i - 1]));
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
       allocator_traits<Allocator>::construct(alloc, vector + i - 1, move_if_noexcept(vector[i]));
        allocator_traits<Allocator>::destroy(alloc, vector + i);
      }

      --curr_idx;
      return vector + index;
    }

  //ištrina elementus nurodytoje atkarpoje
  T* erase(T* first, T* last) {
    size_t start = first - vector;
    size_t end = last - vector;
    size_t count = end - start;

    // Move tail elements forward
    for (size_t i = end; i < curr_idx; ++i) {
        vector[i - count] = std::move(vector[i]);
    }

    // Destroy the now-unused tail elements
    for (size_t i = curr_idx - count; i < curr_idx; ++i) {
        allocator_traits<Allocator>::destroy(alloc, vector + i);
    }

    curr_idx -= count;
    return vector + start;
}

   //prideda elementą į vektoriaus pabaigą
 void push_back(const T& value) {


    if (curr_idx >= cpct) {
        size_t new_cpct = (cpct == 0) ? 1 : cpct * 2;

        reserve(new_cpct);  // Reserve memory without changing curr_idx
    }
    std::allocator_traits<Allocator>::construct(alloc, vector + curr_idx, value);
    ++curr_idx;
}


    //įterpia objektą į vektoriaus pabaigą iš karto naudojant konstruktorių
    template <typename... Args>
void emplace_back(Args&&... args) {

    if (curr_idx == cpct) {
        reserve(cpct == 0 ? 1 : cpct * 2);
    }

   allocator_traits<Allocator>::construct(alloc, vector + curr_idx, forward<Args>(args)...);

    ++curr_idx;
}

// Pašalina paskutinį elementą.
    void pop_back() {
        if (curr_idx > 0) {
            --curr_idx;
            destroy_at(vector + curr_idx);
        }
    }
    // Pakeičia vektoriaus dydį.
    // Jei naujas dydis mažesnis už dabartinį, elementai gale yra sunaikinami.
    // Jei naujas dydis didesnis, nauji elementai yra pridedami ir inicializuojami pagal nutylėjimą.
    void resize(size_type new_size) {
    if (new_size < curr_idx) {
        for (size_t i = new_size; i < curr_idx; ++i) {
            std::allocator_traits<Allocator>::destroy(alloc, vector + i);
        }
    } else if (new_size > curr_idx) {
        if (new_size > cpct) {
            reserve(std::max((cpct == 0 ? 1 : cpct * 2), new_size));
        }
        for (size_type i = curr_idx; i < new_size; ++i) {
            std::allocator_traits<Allocator>::construct(alloc, vector + i); // Assumes T is default-constructible
        }
    }

    curr_idx = new_size;
}

    // Pakeičia vektoriaus dydį.
    // Jei naujas dydis didesnis, nauji elementai yra pridedami ir inicializuojami duota reikšme (value).
    void resize(size_type new_size, const value_type& value) {
        if (new_size < curr_idx) {
            destroy_range(vector + new_size, vector + curr_idx);
        } else if (new_size > curr_idx) {
            if (new_size > cpct) {
                reserve(max(cpct == 0 ? 1 : cpct * 2, new_size));
            }
            for (size_type i = curr_idx; i < new_size; ++i) {
                allocator_traits<Allocator>::construct(alloc, vector + i, value);
            }
        }
        curr_idx = new_size;
    }
    void swap(Vector& other) noexcept {
    	swap(vector, other.vector);
    	swap(cpct, other.cpct);
    	swap(curr_idx, other.curr_idx);
    	swap(alloc, other.alloc);
}

};
//NON-MEMBER FUNCTIONS

    template<class T, class Allocator>
bool operator==(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    return equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<class T, class Allocator>
bool operator!=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {
    return !(lhs == rhs);
}
template<class T, class Allocator>
bool operator<(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<class T, class Allocator>
bool operator<=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {
    return !(rhs < lhs);
}

template<class T, class Allocator>
bool operator>(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {
    return rhs < lhs; // Daugiau yra tas pats, kas "dešinė pusė mažesnė už kairę".
}

template<class T, class Allocator>
bool operator>=(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) {
    return !(lhs < rhs);
}

template <typename T, typename Allocator>
void swap(Vector<T, Allocator>& lhs, Vector<T, Allocator>& rhs) noexcept {
    lhs.swap(rhs);
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i] << "\n";
    }
    return os;
}