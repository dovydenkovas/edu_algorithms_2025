#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <exception>
#include <iostream>

template <class T> class vector {
private:
  T *array = nullptr;
  size_t allocated_size = 0;
  size_t vector_size = 0;
  void copy(T *from, T *to, size_t size);

public:
  class iterator;

  vector() {
    reserve(10);
    fill({});
  }
  vector(size_t new_size) { resize(new_size); }

  vector(const vector &other);
  vector(vector &&other);

  vector &operator=(const vector &other);
  vector &operator=(vector &&other);

  T &operator[](size_t index);
  T const &operator[](size_t index) const;

  size_t size() const { return vector_size; }
  size_t capacity() const { return allocated_size; }
  bool empty() const { return vector_size == 0; }

  void push_back(T item);
  void pop_back();

  void insert(size_t index, T item);
  void erase(size_t index);

  void reserve(size_t new_size);
  void resize(size_t new_size);
  void fill(T value);

  iterator begin() { return iterator{array}; }
  iterator end() { return iterator{array + vector_size}; }

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
  T *new_array = new T[new_size];
  copy(array, new_array, std::min(vector_size, new_size));
  delete[] array;
  array = new_array;
  allocated_size = new_size;
  vector_size = std::min(vector_size, new_size);
}

template <class T> void vector<T>::resize(size_t new_size) {
  if (new_size > allocated_size) {
    T *new_arr = new T[new_size];
    size_t n = std::min(new_size, vector_size);
    copy(array, new_arr, n);
    delete[] array;
    array = new_arr;
  }

  while (vector_size < new_size) {
    array[vector_size] = {};
    ++vector_size;
  }
}

template <class T> void vector<T>::fill(T value) {
  for (size_t i = 0; i < size(); ++i)
    array[i] = value;
}

template <class T> vector<T>::vector(const vector &other) {
  reserve(other.allocated_size);
  for (size_t i = 0; i < other.size(); ++i)
    array[i] = other[i];
  vector_size = other.vector_size;
}

template <class T> vector<T>::vector(vector &&other) {
  array = other.array;
  vector_size = other.vector_size;
  allocated_size = other.allocated_size;
  other.vector_size = 0;
  other.allocated_size = 0;
  other.array = nullptr;
}

template <class T> vector<T> &vector<T>::operator=(const vector &other) {
  reserve(other.vector_size);
  for (int i = 0; i < other.size(); ++i)
    array[i] = other[i];
  vector_size = other.vector_size;
  return *this;
}

template <class T> vector<T> &vector<T>::operator=(vector &&other) {
  std::cout << "AB\n";
  delete this->array;
  array = other.array;
  vector_size = other.vector_size;
  allocated_size = other.allocated_size;
  other.vector_size = 0;
  other.allocated_size = 0;
  other.array = nullptr;
  return *this;
}

template <class T> T &vector<T>::operator[](size_t index) {
  if (index < size())
    return array[index];
  throw std::exception();
}

template <class T> T const &vector<T>::operator[](size_t index) const {
  if (index < size())
    return array[index];
  throw std::exception();
}

template <class T> void vector<T>::push_back(T item) {
  if (vector_size + 1 >= allocated_size)
    reserve(2 * allocated_size);

  array[vector_size] = item;
  ++vector_size;
}

template <class T> void vector<T>::pop_back() {
  if (empty())
    return;

  --vector_size;
  if (vector_size < allocated_size * 0.5)
    reserve(allocated_size * 0.5);
}

template <class T> void vector<T>::insert(size_t index, T item) {
  resize(vector_size + 1);
  for (size_t i = vector_size - 1; i > index; --i) {
    array[i] = array[i - 1];
  }
  array[index] = item;
}

template <class T> void vector<T>::erase(size_t index) {
  for (size_t i = index; i < size() - 1; ++i)
    array[i] = array[i + 1];
  pop_back();
}

#endif
