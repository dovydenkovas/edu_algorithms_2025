#include "vector.hpp"
#include <algorithm>
#include <cstdint>
#include <ctype.h>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

using std::wstring;

// Хеш-функция строк
uint32_t string_hash(std::string key) {
  uint16_t h = 0;
  for (auto &ch : key)
    h ^= int((ch - ' ') * UINT32_MAX / (127 - ' '));
  return h;
}

template <class K, class V, uint32_t hash(K)> class hashmap {
private:
  using item = std::pair<K, V>;
  vector<item *> data;
  size_t keys_count;
  item *nil = nullptr;
  item *removed;

  size_t get(K &key) const;
  void resize(size_t new_size);

public:
  class iterator;

  hashmap() : data{16}, keys_count{0}, removed{new item} { data.fill(nil); }
  hashmap(hashmap &other) { *this = other; }
  hashmap(hashmap &&other) { *this = other; }

  hashmap &operator=(hashmap &other);
  hashmap &&operator=(hashmap &&other);

  V &operator[](K &key);
  V operator[](K &key) const;

  size_t size() { return keys_count; }
  bool empty() { return keys_count == 0; }

  bool contains(K &key) const;
  void insert(K key, V &&value);
  void erase(K &key);

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
    delete removed;
  }
};
/*
template <class K, class V, uint32_t hash(K)>
class hashmap<K, V, hash>::iterator {
  using item = std::pair<K, V>;
  vector<item *>::iterator it;
  item *removed;
  vector<item *>::iterator end;

public:
  explicit iterator(vector<item *>::iterator it, item *removed, vector<item *>::iterator end)
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
  K operator*() const { return (*it)->first; }
};
*/

template <class K, class V, uint32_t hash(K)>
void hashmap<K, V, hash>::resize(size_t new_size) {
  vector<item *> old = data;
  data.resize(new_size);
  data.fill(nil);
  for (auto &p : old) {
    if (p != nil && p != removed) {
      insert(p->first, std::move(p->second));
    }
  }
}

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

template <class K, class V, uint32_t hash(K)>
V &hashmap<K, V, hash>::operator[](K &key) {
  return data[get(key)]->second;
}

template <class K, class V, uint32_t hash(K)>
V hashmap<K, V, hash>::operator[](K &key) const {
  return data[get(key)]->second;
}

template <class K, class V, uint32_t hash(K)>
void hashmap<K, V, hash>::insert(K key, V &&value) {
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

template <class K, class V, uint32_t hash(K)>
void hashmap<K, V, hash>::erase(K &key) {
  size_t index = get(key);
  delete data[index];
  data[index] = removed;
  --keys_count;
}

template <class K, class V, uint32_t hash(K)>
bool hashmap<K, V, hash>::contains(K &key) const {
  try {
    get(key);
    return true;
  } catch (...) {
    return false;
  }
}
