#include "vector.h"

template<class T>
Vector<T>::Vector() : array(nullptr), len(0) {}

template<class T>
Vector<T>::Vector(const Vector &obj) : len(obj.len) {
    array = (T *) new char[len * sizeof(T)];
    for (size_t i = 0; i < len; ++i)
        new(array + i) T(obj.array[i]);
}

template<class T>
Vector<T>::~Vector() {
    for (size_t i = 0; i < len; ++i)
        (array + i)->~T();
    delete[] (char *) array;
}

template<class T>
Vector<T> & Vector<T>::operator=(const Vector<T> &obj) {
    if (array != obj.array) {
        for (size_t i = 0; i < len; ++i)
            (array + i)->~T();
        delete[] (char *) array;
        len = obj.len;
        array = (T *) new char[len * sizeof(T)];
        for (size_t i = 0; i < len; ++i)
            new(array + i) T(obj.array[i]);

    }
    return *this;
}

template<class T>
template <class V, size_t N>
Vector<T> & Vector<T>::operator=(const V (&obj)[N]) {
    if (array != obj) {
        for (size_t i = 0; i < len; ++i)
            (array + i)->~T();
        delete [] (char *) array;
        len = N;
        array = (T*) new char[len * sizeof(T)];
        for (size_t i = 0; i < len; ++i)
            new(array + i) T(obj[i]);

    }
    return *this;
}

template<class T>
template<class V>
void Vector<T>::push_back(const V &a) {
    T* cur_alloc = array;
    array = (T*) new char[++len * sizeof(T)];
    for (size_t i = 0; i < len - 1; i++)
        array[i] = cur_alloc[i];
    array[len - 1] = a;
    delete [] (char *) cur_alloc;
}

template<class T>
void Vector<T>::pop_back() {
    T* cur_alloc = array;
    array = (T*) new char[--len * sizeof(T)];
    for (size_t i = 0; i < len; i++)
        array[i] = cur_alloc[i];
    delete [] (char *) cur_alloc;
}

template <class T>
void Vector<T>::clear() {
    for (size_t i = 0; i < len; ++i)
        (array + i)->~T();
    delete [] (char *) array;
    len = 0;
}

template <class T>
template<class Comp>
T Vector<T>::minimum(const Vector &a) {
    T temp = a[0];
    for (size_t i = 1; i < a.size(); ++i)
        if (Comp(a[i], temp))
            temp = a[i];
    return temp;

}

template <class T>
bool Vector<T>::empty() const { return len == 0; }

template <class T>
size_t Vector<T>::size() const { return len; }

template <class T>
const T * const Vector<T>::begin() { return array; }

template <class T>
T& Vector<T>::operator[](size_t i) {return *(array + i); }
