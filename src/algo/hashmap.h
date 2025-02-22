#include <ctype.h>
#include <algorithm>
#include <exception>

template <class K, class V>
class hashmap {
  private:
    void resize(size_t new_size)
    {
    }

  public: 
    hashmap() { }
    hashmap(hashmap& other) { *this = other; }
    hashmap(hashmap&& other) { *this = other; }
    
    hashmap& operator=(hashmap& other)
    {
    }

    hashmap&& operator=(hashmap&& other) 
    {
    }

    V& operator[](K& key) 
    {
    }

    V const & operator[](K& key) const
    {
    }

    
    size_t size() {}
    bool empty() {}

    void insert(K&& key, V&& value) 
    {
    }

    void erase(K& key)
    {
    }    

    class iterator {
      K* ptr; 
      public:
        explicit iterator(K* it) : ptr(it) {}
        iterator& operator++() { ++ptr; return *this; }
        iterator operator++(int) {iterator retval = *this; ++(*this); return retval; }
        bool operator==(iterator other) const { return ptr == other.ptr; }
        bool operator!=(iterator other) const { return !(*this == other); }
        K& operator*() const {return this;}
    };

    iterator begin() {return iterator{};}
    iterator end() {return iterator{};}

    ~hashmap() {  }

  };
