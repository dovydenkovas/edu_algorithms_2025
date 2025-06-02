#pragma once

#include "vector.hpp"
#include <algorithm>
#include <cstdint>
#include <ctype.h>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

namespace algo {

template <class K, class V, uint32_t hash(K)> class hashmap {
private:
  using item = std::pair<K, V>;
  vector<item *> data;
  size_t keys_count;
  item *nil = nullptr;
  item *removed = nullptr;

  size_t get(K &key) const;
  void resize(size_t new_size);

public:
  class iterator;

  explicit hashmap() : data{16}, keys_count{0}, removed{(item*)this} { data.fill(nil); }
  explicit hashmap(hashmap &other) : data{}, keys_count{0}, removed{(item*)this} {
    *this = other;
  }

  hashmap &operator=(const hashmap &other);

  V &operator[](K key);
  V operator[](K key) const;

  size_t size() { return keys_count; }
  bool empty() { return keys_count == 0; }

  bool contains(K key) const;
  void insert(K key, V value);
  void erase(K key);
  void clear();

  iterator begin() {
    auto it = data.begin();
    while (it != data.end() && (*it == nullptr || *it == removed)) {
      ++it;
    }
    return iterator{it, removed, data.end()};
  }
  iterator end() { return iterator{data.end(), removed, data.end()}; }

  ~hashmap() {
    for (auto &p : data)
      if (p != nil && p != removed)
        delete p;
  }
};

template <class K, class V, uint32_t hash(K)>
hashmap<K, V, hash> &
hashmap<K, V, hash>::operator=(const hashmap<K, V, hash> &other) {
  data.resize(other.data.size());
  keys_count = other.keys_count;
  for (int i = 0; i < data.size(); ++i)
    if (data[i] == other.removed)
      data[i] = removed;
    else if (other.data[i] == nil)
      data[i] = nil;
    else
      data[i] = new item{other.data[i]->first, other.data[i]->second};

  return *this;
}

template <class K, class V, uint32_t hash(K)>
class hashmap<K, V, hash>::iterator {
  typename vector<item *>::iterator it;
  item *removed;
  typename vector<item *>::iterator end;

public:
  explicit iterator(typename vector<item *>::iterator it, item *removed,
                    typename vector<item *>::iterator end)
      : it(it), removed(removed), end(end) {}
  iterator &operator++() {
    ++it;
    while (it != end && (*it == nullptr || *it == removed))
      ++it;
    return *this;
  }

  iterator operator++(int) {
    iterator retval = *this;
    ++(*this);
    return retval;
  }

  bool operator==(iterator other) const { return it == other.it; }
  bool operator!=(iterator other) const { return !(*this == other); }
  std::pair<K, V> operator*() const { return *(*it); }
};

// Масштабирует таблицу с пересчетом адресов всех элементов.
template <class K, class V, uint32_t hash(K)>
void hashmap<K, V, hash>::resize(size_t new_size) {
  vector<item *> old = data;
  keys_count = 0;
  data.resize(new_size);
  data.fill(nil);
  for (auto &p : old) {
    if (p != nil && p != removed) {
      insert(p->first, std::move(p->second));
    }

    delete p;
  }
}

// Возвращает индекс значения в таблице по ключу.
// Если ключа нет - вызывает исключение.
template <class K, class V, uint32_t hash(K)>
size_t hashmap<K, V, hash>::get(K &key) const {
  uint32_t h = hash(key) % data.size();
  for (size_t i = 0; i < data.size(); ++i) {
    size_t index = (h + i) % data.size();
    if (data[index] == nil)
      break;
    if (data[index] == removed)
      continue;

    if (data[index]->first == key) {
      return index;
    }
  }
  throw std::out_of_range("Ключ вне диапазона.");
}

// Возвращает значение по ключу.
// Если ключа нет - вызывает исключение.
template <class K, class V, uint32_t hash(K)>
V &hashmap<K, V, hash>::operator[](K key) {
  return data[get(key)]->second;
}

// Возвращает значение по ключу.
// Если ключа нет - вызывает исключение.
template <class K, class V, uint32_t hash(K)>
V hashmap<K, V, hash>::operator[](K key) const {
  return data[get(key)]->second;
}

// Добавляет пару ключ-значение в дерево.
// Если ключ уже добавлен - вызывает исключение.
template <class K, class V, uint32_t hash(K)>
void hashmap<K, V, hash>::insert(K key, V value) {
  if (keys_count + 1 >= data.size())
    resize(data.size() * 2);

  uint32_t h = hash(key) % data.size();
  for (size_t i = 0; i < data.size(); ++i) {
    size_t index = (h + i) % data.size();
    if (data[index] == nil || data[index] == removed) {
      data[index] = new std::pair<K, V>{key, value};
      ++keys_count;
      return;
    }

    if (data[index]->first == key) {
      data[index]->second = value;
      return;
    }
  }
}

// Удаляет элемент из таблицы.
// Если ключа нет - вызывает исключение.
template <class K, class V, uint32_t hash(K)>
void hashmap<K, V, hash>::erase(K key) {
  size_t index = get(key);
  delete data[index];
  data[index] = removed;
  --keys_count;
}

// Удаляет все элементы из таблицы.
template <class K, class V, uint32_t hash(K)>
void hashmap<K, V, hash>::clear() {
  for (auto &item: data)
    delete item;
  data.fill(nil);
  data.resize(16);
  keys_count = 0;
}

// Возвращает true, если ключ есть в таблице.
template <class K, class V, uint32_t hash(K)>
bool hashmap<K, V, hash>::contains(K key) const {
  try {
    get(key);
    return true;
  } catch (...) {
    return false;
  }
}
}; // namespace algo
