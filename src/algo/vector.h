#include <ctype.h>
#include <algorithm>
#include <exception>

template <class T>
class vector {
  private:
    T* arr = nullptr;
    size_t arr_size = 0;
    size_t items_count = 0;

    void set_size(size_t new_size) 
    {
      delete[] arr; 
      arr = new T[new_size];
      arr_size = new_size;
      items_count = 0;
    }

    void resize(size_t new_size)
    {
      T* new_arr = new T[new_size];
      
      size_t n = std::min(new_size, items_count);
      for (int i=0; i<n; ++i)
        new_arr[i] = arr[i];
      
      arr_size = new_size;
      items_count = n;
      delete[] arr;
      arr = new_arr;
    }

    void fill(T value)
    {
      for (int i=0; i<size(); ++i)
        arr[i] = value;
    }

  public: 
    vector() { set_size(10); fill(0); }
    vector(size_t new_size) {set_size(new_size);}
    vector(vector& other) { *this = other; }
    vector(vector&& other) { *this = other; }
    
    vector& operator=(vector& other)
    {
      set_size(other.arr_size);
      for (int i=0; i<other.size(); ++i) 
          this[i] = other[i];
      return *this;
    }

    vector&& operator=(vector&& other) 
    {
      delete this->arr;
      arr = other.arr;
      items_count = other.items_count;
      arr_size = other.arr_size;
      other.items_count = 0;
      other.arr_size = 0;
      other.arr = nullptr;
    }

    T& operator[](size_t index) 
    {
      if (index < size()) 
        return arr[index];
      throw std::exception();
    }

    T const & operator[](size_t index) const
    {
      if (index < size()) 
        return arr[index];
      throw std::exception();
    }

    
    size_t size() {return items_count;}
    bool empty() {return items_count == 0;}

    void push_back(T item) {
      if (items_count+1 >= arr_size)
        resize(arr_size + std::max(10.0, arr_size*0.10));
        
      arr[items_count] = item; 
      ++items_count;

    }

    T pop_back()
    {
      if (empty())
        return;

      --items_count;
      T item = arr[items_count];
      
      if (items_count < arr_size*0.8)
        resize(arr_size*0.8);
      
      return item;
    }    

    void insert(size_t index, T item)
    {
      push_back(item);
      for (int i=items_count-1; i>index; --i) {
        arr[i] = arr[i-1];
      }
      arr[index] = item;
    }

    void erase(size_t index) 
    {
      for (int i=index; i<size()-1; ++i)
        arr[i] = arr[i+1];
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

    iterator begin() {return iterator{arr};}
    iterator end() {return iterator{arr+arr_size};}

    ~vector() { delete[] arr; }

  };
