#pragma once

#include <algorithm>
#include <exception>
#include <initializer_list>
#include <iostream>

namespace algo {
template <class T> class vector {
private:
  T *array = nullptr;
  size_t vec_capacity = 0;
  size_t vec_size = 0;
  void copy(T *from, T *to, size_t size);

public:
  class iterator;

  explicit vector() { reserve(10); }
  explicit vector(std::initializer_list<T> lst) {
    reserve(10);
    for (auto &item: lst )
      push_back(item);
  }
  explicit vector(size_t new_size) { resize(new_size); }
  vector(const vector &other);

  vector &operator=(const vector &other);

  T &operator[](size_t index) {return array[index];};
  T const &operator[](size_t index) const {return array[index];};

  size_t size() const { return vec_size; }
  size_t capacity() const { return vec_capacity; }
  bool empty() const { return vec_size == 0; }

  void push_back(T item);
  void pop_back();

  void insert(size_t index, T item);
  void erase(size_t index);
  void clear();

  void reserve(size_t new_size);
  void resize(size_t new_size);
  void fill(T value);

  iterator begin() { return iterator{array}; }
  iterator end() { return iterator{array + vec_size}; }

  ~vector() { delete[] array; }
};

template <class T> class vector<T>::iterator {
  T *ptr;

public:
  explicit iterator(T *it) : ptr(it) {}
  iterator &operator++() {
    ++ptr;
    return *this;
  }
  iterator operator++(int) {
    iterator retval = *this;
    ++(*this);
    return retval;
  }
  bool operator==(iterator other) const { return ptr == other.ptr; }
  bool operator!=(iterator other) const { return !(*this == other); }
  T &operator*() const { return *ptr; }
};

template <class T> void vector<T>::copy(T *from, T *to, size_t size) {
  for (size_t i = 0; i < size; ++i)
    to[i] = from[i];
}

template <class T> void vector<T>::reserve(size_t new_size) {
  if (new_size > vec_capacity) {
    T *new_arr = new T[new_size];
    size_t n = std::min(new_size, vec_size);
    copy(array, new_arr, n);
    delete[] array;
    array = new_arr;
    vec_capacity = new_size;
  }
  vec_size = std::min(vec_size, new_size);
}

template <class T> void vector<T>::resize(size_t new_size) {
  reserve(new_size);
  while (vec_size < new_size) {
    array[vec_size] = {};
    ++vec_size;
  }
}

template <class T> void vector<T>::fill(T value) {
  for (size_t i = 0; i < size(); ++i)
    array[i] = value;
}

template <class T> vector<T>::vector(const vector &other) {
  reserve(other.vec_capacity);
  for (size_t i = 0; i < other.size(); ++i)
    array[i] = other[i];
  vec_size = other.vec_size;
}

template <class T> vector<T> &vector<T>::operator=(const vector &other) {
  reserve(other.vec_size);
  for (size_t i = 0; i < other.size(); ++i)
    array[i] = other[i];
  vec_size = other.vec_size;
  return *this;
}

template <class T> void vector<T>::push_back(T item) {
  if (vec_size + 1 >= vec_capacity)
    reserve(2 * vec_capacity);

  array[vec_size] = item;
  ++vec_size;
}

template <class T> void vector<T>::pop_back() {
  if (empty())
    return;

  --vec_size;
  if (vec_size < vec_capacity * 0.5)
    reserve(vec_capacity * 0.5);
}

template <class T> void vector<T>::insert(size_t index, T item) {
  resize(vec_size + 1);
  for (size_t i = vec_size - 1; i > index; --i) {
    array[i] = array[i - 1];
  }
  array[index] = item;
}

template <class T> void vector<T>::erase(size_t index) {
  for (size_t i = index; i < size() - 1; ++i)
    array[i] = array[i + 1];
  pop_back();
}

template <class T> void vector<T>::clear() {
  if (array)
    delete[] array;
  array = nullptr;
  vec_capacity = 0;
  vec_size = 0;
  reserve(10);
}

}; // namespace algo
