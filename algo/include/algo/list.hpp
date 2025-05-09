#pragma once
#include <cstdlib>
#include <iostream>
#include <ostream>

namespace algo {
template <class T> class list {
private:
  struct Node {
    T data;
    Node *next;

    Node(Node &) = delete;
    Node(Node &&) = delete;
    Node(T data, Node *next) : data{data}, next{next} {}
  };

  class iterator;
  Node *first = nullptr;
  Node *last = nullptr;
  size_t list_size = 0;
  Node *get_prev_node(Node *nxt);
  Node *as_node(iterator it);
  Node *merge_sort(Node *before_first, Node *first, size_t size);

public:
  explicit list() {}
  list(const list &other);
  list &operator=(const list &other);

  size_t size() const { return list_size; }
  bool empty() const { return list_size == 0; }

  iterator push_back(T item);
  void pop_back();

  iterator insert(iterator position, T item);
  iterator erase(iterator posistion);
  void clear();
  void sort();

  iterator begin() const { return iterator{first, first, false}; }
  iterator end() const { return iterator{last, first, true}; }

  ~list() { clear(); }
};

template <class T> class list<T>::iterator {
  Node *ptr;
  Node *first;
  bool is_end;

public:
  explicit iterator(Node *it, Node *root, bool is_end_)
      : ptr(it), first(root), is_end(is_end_) {}
  iterator &operator++() {
    if (ptr->next == first)
      is_end = true;
    else
      ptr = ptr->next;
    return *this;
  }
  iterator operator++(int) {
    iterator retval = *this;
    ++(*this);
    return retval;
  }
  bool operator==(iterator other) const {
    return ptr == other.ptr && is_end == other.is_end;
  }
  bool operator!=(iterator other) const { return !(*this == other); }
  T &operator*() { return ptr->data; }

  friend Node *list<T>::as_node(iterator it);
};

template <class T> list<T>::list(const list &other) {
  clear();
  for (auto &item : other)
    push_back(item);
}

template <class T> list<T> &list<T>::operator=(const list &other) {
  clear();
  for (auto &item : other)
    push_back(item);
  return *this;
}

template <class T> typename list<T>::iterator list<T>::push_back(T item) {
  Node *node = new Node{item, first};

  if (!first) { // Для первого элемента.
    first = node;
    last = node;
  }

  last->next = node;
  last = node;

  ++list_size;
  return iterator{node, first, false};
}

template <class T> typename list<T>::Node *list<T>::get_prev_node(Node *nxt)
{
  if (!first)
    return nullptr;
  Node *node = first;
  while (node->next != nxt && node->next != first)
    node = node->next;
  return node;
}

template <class T> typename list<T>::Node *list<T>::as_node(iterator it) {
  return it.ptr;
}

template <class T> void list<T>::pop_back() {
  if (empty())
    return;

  Node *node = first;
  while (node->next->next != first)
    node = node->next;

  delete last;
  --list_size;

  if (node->next == first) {
    first = nullptr;
    last = nullptr;
  } else {
  node->next = first;
  last = node;
  }
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator position, T item) {
  if (empty() || position == end())
    return push_back(item);

  Node *prev = get_prev_node(as_node(position));
  Node *node = new Node{item, prev->next};
  prev->next = node;
  ++list_size;
  return iterator{node, first, false};
}

template <class T>
typename list<T>::iterator list<T>::erase(iterator position) {
  if (empty() || position == end())
    return end();

  Node *prev_elem = get_prev_node(as_node(position));
  prev_elem->next = as_node(position)->next;
  if (as_node(position) == first)
    first = as_node(position)->next;
  delete as_node(position);
  --list_size;
  return iterator(prev_elem->next, first, false);
}

template <class T> void list<T>::clear() {
  if (list_size == 0)
    return;

  for (Node *node = first; node != last;) {
    auto del = node;
    node = node->next;
    delete del;
  }
  delete last;
  first = nullptr;
  last = nullptr;
}

template <class T> void list<T>::sort() {
  size_t lst_size = size();

  if (lst_size <= 1)
    return;

  first = merge_sort(nullptr, first, lst_size);

  // Восстановить указатель на последний элемент и
  // цикличность списка
  Node *node = first;
  for (int i = 0; i < lst_size - 1; ++i)
    node = node->next;

  node->next = first;
  last = node;
}

template <class T>
typename list<T>::Node *list<T>::merge_sort(typename list<T>::Node *before_left,
                                            typename list<T>::Node *left,
                                            size_t size) {
  // Крайний случай для длины 0 или 1
  if (size <= 1)
    return left;

  // Крайний случай для пары элементов
  if (size == 2) {
    Node *right = left->next;
    if (left->data > right->data) {
      if (before_left)
        before_left->next = right;
      left->next = right->next;
      right->next = left;
      return right;
    }

    return left;
  }

  Node *ptrr = left;
  for (int i = 0; i < size; ++i)
    ptrr = ptrr->next;

  // Сортируем первую половину до середины (округление вверх)
  left = merge_sort(before_left, left, size / 2 + size % 2);
  // Сортируем вторую половину начиная с середины (округление вниз)

  Node *before_right = left;
  for (int i = 1; i < size / 2.0; ++i) {
    before_right = before_right->next;
  }
  Node *right = merge_sort(before_right, before_right->next, size / 2);

  // Подготовка к слиянию
  Node *new_root = nullptr;
  size_t left_size = size / 2 + size % 2;
  size_t right_size = size / 2;

  // Определение нового корня
  if (left->data <= right->data) {
    new_root = left;
    left = left->next;
    --left_size;
  } else {
    new_root = right;
    if (before_left)
      before_left->next = right;
    right = right->next;
    --right_size;
  }

  Node *ptr = new_root;
  // Главный цикл слияния
  while (left_size != 0 && right_size != 0) {
    if (left->data <= right->data) {
      ptr->next = left;
      left = left->next;
      --left_size;
    } else {
      ptr->next = right;
      right = right->next;
      --right_size;
    }
    ptr = ptr->next;
  }

  // Если закончились правые элементы
  if (right_size == 0) {
    // элемент, следующий за сортируемой последовательностью
    Node *after_last = ptr->next;
    ptr->next = left;
    while (left_size != 0) {
      --left_size;
      ptr = ptr->next;
    }
    ptr->next = after_last;
  } else {
    ptr->next = right;
  }

  return new_root;
}

}; // namespace algo
