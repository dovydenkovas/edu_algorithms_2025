#include <ctype.h>
#include <algorithm>
#include <exception>

template <class T>
class vector {
  private:
    T* array = nullptr;
    size_t allocated_size = 0;
    size_t vector_size = 0;
    void reserve(size_t new_size);

  public:
    vector() { reserve(10); fill({}); }
    vector(size_t new_size) {reserve(new_size); fill({});}
    vector(const vector& other);
    vector(vector&& other);

    vector& operator=(const vector& other);
    vector& operator=(vector&& other);

    T& operator[](size_t index);
    T const & operator[](size_t index) const;

    size_t size() const {return vector_size;}
    size_t capacity() const {return allocated_size;}
    bool empty() const {return vector_size == 0;}

    void push_back(T item);
    void pop_back();

    void insert(size_t index, T item);
    void erase(size_t index);


    void resize(size_t new_size);
    void fill(T value);

    class iterator {
      T* ptr;
      public:
        explicit iterator(T* it) : ptr(it) {}
        iterator& operator++() { ++ptr; return *this; }
        iterator operator++(int) {iterator retval = *this; ++(*this); return retval; }
        bool operator==(iterator other) const { return ptr == other.ptr; }
        bool operator!=(iterator other) const { return !(*this == other); }
        T& operator*() const {return *ptr;}
    };

    iterator begin() {return iterator{array};}
    iterator end() {return iterator{array+vector_size};}

    ~vector() { delete[] array; }
};


template <class T>
void vector<T>::reserve(size_t new_size)
{
    delete[] array;
    array = new T[new_size];
    allocated_size = new_size;
    vector_size = 0;
}

template <class T>
void vector<T>::resize(size_t new_size)
{
    T* new_arr = new T[new_size];

    size_t n = std::min(new_size, vector_size);
    for (int i=0; i<n; ++i)
        new_arr[i] = array[i];

    allocated_size = new_size;
    vector_size = n;
    delete[] array;
    array = new_arr;
}

template <class T>
void vector<T>::fill(T value)
{
    for (int i=0; i<size(); ++i)
        array[i] = value;
}


template <class T>
vector<T>::vector(const vector& other)
{
    reserve(other.allocated_size);
    for (int i=0; i<other.size(); ++i)
        array[i] = other[i];
    vector_size = other.vector_size;
}

template <class T>
vector<T>::vector(vector&& other)
{
    array = other.array;
    vector_size = other.vector_size;
    allocated_size = other.allocated_size;
    other.vector_size = 0;
    other.allocated_size = 0;
    other.array = nullptr;
}

template <class T>
vector<T>& vector<T>::operator=(const vector& other)
{
    reserve(other.vector_size);
    for (int i=0; i<other.size(); ++i)
        array[i] = other[i];
    vector_size = other.vector_size;
    return *this;
}


template <class T>
vector<T>& vector<T>::operator=(vector&& other)
{
    delete this->array;
    array = other.array;
    vector_size = other.vector_size;
    allocated_size = other.allocated_size;
    other.vector_size = 0;
    other.allocated_size = 0;
    other.array = nullptr;
    return *this;
}

template <class T>
T& vector<T>::operator[](size_t index)
{
    if (index < size())
        return array[index];
    throw std::exception();
}

template <class T>
T const & vector<T>::operator[](size_t index) const
{
    if (index < size())
        return array[index];
    throw std::exception();
}

template <class T>
void vector<T>::push_back(T item) {
    if (vector_size+1 >= allocated_size)
        resize(2*allocated_size);

    array[vector_size] = item;
    ++vector_size;
}


template <class T>
void vector<T>::pop_back()
{
    if (empty())
        return;

    --vector_size;
    T item = array[vector_size];

    if (vector_size < allocated_size*0.5)
        resize(allocated_size*0.5);
}

template <class T>
void vector<T>::insert(size_t index, T item)
{
    push_back(item);
    for (int i=vector_size-1; i>index; --i) {
        array[i] = array[i-1];
    }
    array[index] = item;
}

template <class T>
void vector<T>::erase(size_t index)
{
    for (int i=index; i<size()-1; ++i)
        array[i] = array[i+1];
    pop_back();
}

#ifdef TEST
#include <iostream>

vector<double> foo()
{
    vector<double> arr;

      for (int i=0; i<100; i++) {
        arr.push_back(i);
        std::cout << arr[i] << std::endl;
      }
      return arr;
}


int main()
{
    vector<double> arr(foo());

    for (int i = 0; i < 25; ++i)
        arr.erase(i);

    for (auto &a: arr) {
        std::cout << a << " ";
    }
    std::cout << std::endl;

    vector<double> vec;

    vec = arr;
    vec[0] = 10;
    vec.insert(1, 2.0);
    for (auto &a: vec) {
        std::cout << a << " ";
    }
    std::cout << std::endl;


    std::cout << vec.size() << " " << vec.capacity() << std::endl;
}
#endif
