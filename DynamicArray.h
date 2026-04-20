/**
 * @file DynamicArray.h
 * @brief Declaration of the templated DynamicArray class.
 */

#pragma once
#include <iostream>

 /**
  * @class DynamicArray
  * @brief A generic dynamic array implementation for contiguous memory storage.
  * @tparam T The data type of the elements to be stored in the array.
  */
template <typename T>
class DynamicArray {
private:
    T* data;      /**< Pointer to the dynamically allocated memory block. */
    int size;     /**< The current number of elements stored in the array. */
    int capacity; /**< The total allocated capacity of the array. */

public:
    /**
     * @brief Default constructor. Initializes an empty array with a default capacity.
     */
    DynamicArray();

    /**
     * @brief Copy constructor.
     * @param other The DynamicArray instance to copy from.
     */
    DynamicArray(const DynamicArray& other);

    /**
     * @brief Destructor. Frees the allocated memory.
     */
    ~DynamicArray();

    /**
     * @brief Copy assignment operator.
     * @param other The DynamicArray instance to assign from.
     * @return A reference to the current instance.
     */
    DynamicArray& operator=(const DynamicArray& other);

    /**
     * @brief Resizes the array to the specified size. Reallocates memory if necessary.
     * @param new_size The target size for the array.
     */
    void resize(int new_size);

    /**
     * @brief Accesses the element at the specified index.
     * @param index The zero-based index of the element.
     * @return A reference to the element.
     */
    T& operator[](int index);

    /**
     * @brief Accesses the element at the specified index (read-only).
     * @param index The zero-based index of the element.
     * @return A constant reference to the element.
     */
    const T& operator[](int index) const;

    /**
     * @brief Retrieves the current number of elements in the array.
     * @return The size of the array.
     */
    int getSize() const;

    /**
     * @brief Overloads the stream insertion operator for outputting array contents.
     * @tparam U The data type of the array elements.
     * @param os The output stream.
     * @param arr The DynamicArray instance to output.
     * @return A reference to the modified output stream.
     */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<U>& arr);
};

#include "DynamicArray.tpp"