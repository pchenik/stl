#include "vector.h"
#include <iostream>

template<class T>
Vector<T>::Vector() : array(nullptr), __size(0), __capacity(0) {}

template<class T>
Vector<T>::Vector(const Vector &obj) : __size(obj.len), __capacity(__size * sizeof(T)) {
    array = (T *) new char[__capacity];
    for (size_t i = 0; i < __size; ++i)
        new(array + i) T(obj.array[i]);
}

template<class T>
Vector<T>::~Vector() {
    for (size_t i = 0; i < __size; ++i)
        (array + i)->~T();
    delete[] (char *) array;
}

template<class T>
Vector<T> & Vector<T>::operator=(const Vector<T> &obj) {
    if (array != obj.array) {
        for (size_t i = 0; i < __size; ++i)
            (array + i)->~T();
        delete[] (char *) array;
        __size = obj.__size;
        __capacity = __size * sizeof(T);
        array = (T *) new char[__capacity];
        for (size_t i = 0; i < __size; ++i)
            new(array + i) T(obj.array[i]);

    }
    return *this;
}

template<class T>
template <class V, size_t N>
Vector<T> & Vector<T>::operator=(const V (&obj)[N]) {
    if (array != obj) {
        for (size_t i = 0; i < __size; ++i)
            (array + i)->~T();
        delete [] (char *) array;
        __size = N;
        __capacity = __size * sizeof(T);
        array = (T*) new char[__capacity];
        for (size_t i = 0; i < __size; ++i)
            new(array + i) T(obj[i]);

    }
    return *this;
}

template<class T>
template<class V>
void Vector<T>::push_back(const V &a) {
    if (__capacity < ++__size * sizeof(T)) {
        T* cur_alloc = array;
        __capacity ^= __capacity << 1;
        array = (T*) new char[__capacity];
        for (size_t i = 0; i < __size - 1; i++)
            array[i] = cur_alloc[i];
        delete [] (char *) cur_alloc;
    }
    array[__size - 1] = a;
}

template<class T>
void Vector<T>::pop_back() {
    if ((__capacity >> 1) > --__size * sizeof(T)) {
        T* cur_alloc = array;
        __capacity = __size * sizeof(T);
        array = (T*) new char[__capacity];
        for (size_t i = 0; i < __size; i++)
            array[i] = cur_alloc[i];
        delete [] (char *) cur_alloc;
    }
}

template <class T>
void Vector<T>::clear() {
    for (size_t i = 0; i < __size; ++i)
        (array + i)->~T();
    delete [] (char *) array;
    __size = __capacity = 0;
    array = 0;
}

template <class T>
template<class Comp>
T Vector<T>::minimum(Comp less) {
    T temp = *this->begin();
    for (const T* it = this->begin(); it != this->end(); ++it)
        if (less(*it, temp))
            temp = *it;
    return temp;

}

template <class T>
bool Vector<T>::empty() const { return __size == 0; }

template <class T>
size_t Vector<T>::size() const { return __size; }

template <class T>
const T * const Vector<T>::begin() { return array; }

template <class T>
const T * const Vector<T>::end() { return array + __size; }

template <class T>
T& Vector<T>::operator[](size_t i) {
    try {
        if (i >= __size)
            throw;
        return *(this->array + i);
    }
    catch(...) {
        std::cout << "Error: out of the boundary of the Vector" << std::endl;
    }
}
