#include <ctype.h>
#include <algorithm>
#include <exception>

template <class T>
class list {
  private:
 
  public: 
    list() {}
    list(size_t new_size) {}
    list(list& other) {  }
    list(list&& other) {  }
    
    list& operator=(list& other)
    {
    }

    list&& operator=(list&& other) 
    {
    }

    T& operator[](size_t index) 
    {
    }

    T const & operator[](size_t index) const
    {
    }

    
    size_t size() {}
    bool empty() {}

    void push_back(T item) {
    }

    T pop_back()
    {
    }    

    void insert(size_t index, T item)
    {
    }

    void erase(size_t index) 
    {
    }

    class iterator {
      T* ptr; 
      public:
        explicit iterator(T* it) : ptr(it) {}
        iterator& operator++() { ++ptr; return *this; }
        iterator operator++(int) {iterator retval = *this; ++(*this); return retval; }
        bool operator==(iterator other) const { return ptr == other.ptr; }
        bool operator!=(iterator other) const { return !(*this == other); }
        T& operator*() const {return this;}
    };

    iterator begin() {return iterator{};}
    iterator end() {return iterator{};}

    ~list() { }

  };
