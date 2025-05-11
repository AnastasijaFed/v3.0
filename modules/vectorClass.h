//
// Created by Anastasija Fedorenko on 2025-05-11.
//

#ifndef VECTORCLASS_H
#define VECTORCLASS_H
#include <cstddef>
#include <stdexcept>

template<class T> class Vector {

    T* vector_ = nullptr;   // pointer to first data element
    size_t capacity_ = 0;   // current memory capacity
    size_t curr_idx_ = 0;   // current vector size (same as numel)

public:
    // ... //same as above

    // Element read/write access
    T& operator[](const size_t index); // return element reference at index
};



#endif //VECTORCLASS_H
