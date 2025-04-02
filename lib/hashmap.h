#include <algorithm>
#include <cstdint>
#include <ctype.h>
#include <exception>
#include <utility>
#include "vector.h"

template <class K, class V> class hashmap {
private:
  uint32_t (&hash)(K);
  vector<std::pair<K, V>> data;

public:
  class iterator;

  hashmap(uint32_t (&hash)(K)): hash{hash}, data{16} {}
  hashmap(hashmap &other): hash{other.hash} { *this = other; }
  hashmap(hashmap &&other): hash{other.hash} { *this = other; }

  hashmap &operator=(hashmap &other);
  hashmap &&operator=(hashmap &&other);

  V &operator[](K &key);
  V operator[](K &key) const;

  size_t size();
  bool empty();

  bool contains(K &key) const;
  void insert(K &&key, V &&value);
  void erase(K &key);

  iterator begin() { return iterator{}; }
  iterator end() { return iterator{}; }

  ~hashmap() {}
};

template <class K, class V> class hashmap<K, V>::iterator {
  vector<std::pair<K, V>>::iterator it;

public:
  explicit iterator(K *it) : ptr(it) {}
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
  K &operator*() const { return this; }
};
