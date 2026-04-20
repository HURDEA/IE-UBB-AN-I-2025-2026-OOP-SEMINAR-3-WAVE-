/**
 * @file DynamicArray.tpp
 * @brief Implementation of the templated DynamicArray class.
 */

#pragma once
#include "DynamicArray.h"

template <typename T>
DynamicArray<T>::DynamicArray() : size(0), capacity(10) {
    data = new T[capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) : size(other.size), capacity(other.capacity) {
    data = new T[capacity];
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename T>
void DynamicArray<T>::resize(int new_size) {
    if (new_size > capacity) {
        capacity = new_size * 2;
        T* new_data = new T[capacity];
        for (int i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }
    size = new_size;
}

template <typename T>
T& DynamicArray<T>::operator[](int index) {
    return data[index];
}

template <typename T>
const T& DynamicArray<T>::operator[](int index) const {
    return data[index];
}

template <typename T>
int DynamicArray<T>::getSize() const {
    return size;
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const DynamicArray<U>& arr) {
    os << "[ ";
    for (int i = 0; i < arr.size; ++i) {
        os << arr.data[i] << (i < arr.size - 1 ? ", " : "");
    }
    os << " ]";
    return os;
}