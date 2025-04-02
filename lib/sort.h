// Замена значений двух итератор местами.
#include <cstddef>
template <class Iterator>
void swap(Iterator a, Iterator b) {
  auto buff = *a;
  *a = *b;
  *b = buff;
}

// Замена значений двух итератор местами.
template <class Iterator>
size_t size(Iterator a, Iterator b) {
  size_t s = 0;
  while (a != b) {
    a++;
    s++;
  }
  return s;
}

template <class Iterator>
Iterator advance(Iterator it, size_t index) {
  for (int i = 0; i < index; ++i) ++it;
  return it;
}



// Сортировка слиянием.
template <class Iterator> void sort(Iterator begin, Iterator end) {

}
