#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H
#include <new>
#include <cstddef>

template<typename T>
struct Less { bool operator()(const T& a, const T& b) {return a < b;} };

template<class T>
struct Vector {

    explicit Vector(size_t size, const T &value = T()) : len(size) {
        array = (T *) new char[len * sizeof(T)];
        for (size_t i = 0; i < len; ++i)
            new(array + i) T(value);
    }
    Vector();
    Vector(const Vector &obj);
    ~Vector();
    Vector &operator=(const Vector &obj);
    template <class V, size_t N>
    Vector &operator=(const V (&obj)[N]);
    template<class V>
    void push_back(const V& a);
    void pop_back();
    void clear();
    template<class  Comp = Less<T>>
    T minimum(const Vector& a);
    bool empty() const;
    size_t size() const;
    T &operator[](size_t i);
    const T * const begin();
    const T &back() const { return *(array + len - 1); }
    const T &operator[](size_t i) const { return *(array + i); }

private:
    T *array;
    size_t len;
    size_t memory_size;
};

#include "vector_imp.tpp"

#endif //VECTOR_VECTOR_H
