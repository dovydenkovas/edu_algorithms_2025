#include <algorithm>
#include <ctype.h>
#include <exception>
#include <iostream>

template <class T> class list {
public:
  class iterator;

private:
  struct Node {
    T data;
    Node *next;

    Node() {};
    Node(Node &) = delete;
    Node(Node &&) = delete;
    Node(T data, Node *next): data{data}, next{next} {}
  };

  Node *first = nullptr;
  Node *last = new Node; // Элемент-заглушка, следующий за последним элементом.
  size_t list_size = 0;
  Node *get_prev_node(Node *nxt);
  Node *as_node(iterator it);

public:
  list() {}
  list(const list &other);
  list(list &&other);

  list &operator=(const list &other);
  list &operator=(list &&other);

  size_t size() const { return list_size; }
  bool empty() const { return list_size == 0; }

  iterator push_back(T item);
  void pop_back();

  iterator insert(iterator position, T item);
  iterator erase(iterator posistion);
  void clear();

  iterator begin() const { return iterator{first}; }
  iterator end() const { return iterator{last}; }

  ~list() {
    clear();
    delete last;
  }
};

template <class T> class list<T>::iterator {
  Node *ptr;

public:
  explicit iterator(Node *it) : ptr(it) {}
  iterator &operator++() {
    ptr = ptr->next;
    return *this;
  }
  iterator operator++(int) {
    iterator retval = *this;
    ++(*this);
    return retval;
  }
  bool operator==(iterator other) const { return ptr == other.ptr; }
  bool operator!=(iterator other) const { return !(*this == other); }
  T &operator*() { return ptr->data; }

  friend Node* list<T>::as_node(iterator it);
};

template <class T> list<T>::list(const list &other) {
  clear();
  for (auto &item : other)
    push_back(item);
}

template <class T> list<T>::list(list &&other) {
  delete last;
  first = other.first;
  last = other.last;
  list_size = other.list_size;
  other.list_size = 0;
  other.first = nullptr;
  other.last = nullptr;
}

template <class T> list<T> &list<T>::operator=(const list &other) {
  clear();
  for (auto &item : other)
    push_back(item);
  return *this;
}

template <class T> list<T> &list<T>::operator=(list &&other) {
  clear();
  delete last;
  first = other.first;
  last = other.last;
  list_size = other.list_size;
  other.list_size = 0;
  other.first = nullptr;
  other.last = nullptr;
  return *this;
}

template <class T> list<T>::iterator list<T>::push_back(T item) {
  Node *node = new Node{item, last};

  if (!first) { // Для первого элемента.
    first = node;
    last->next = first;
  }

  Node *prelast = get_prev_node(last);
  prelast->next = node;
  node->next = last;
  ++list_size;
  return iterator{node};
}

template <class T> list<T>::Node *list<T>::get_prev_node(Node *nxt) {
  if (!first)
    return nullptr;
  Node *node = first;
  while (node->next != nxt && node->next != last)
    node = node->next;
  return node;
}


template <class T> list<T>::Node *list<T>::as_node(iterator it) {
  return it.ptr;
}


template <class T> void list<T>::pop_back() {
  if (empty())
    return;

  Node *node = first;
  while (node->next->next != last)
    node = node->next;

  if (node->next == first)
    first = nullptr;

  delete node->next;
  node->next = last;
  --list_size;
}

template <class T>
list<T>::iterator list<T>::insert(iterator position, T item) {
  if (empty() || position == end())
    return push_back(item);

  Node *prev = get_prev_node(as_node(position));
  Node *node = new Node{item, prev->next};
  prev->next = node;
  ++list_size;
  return iterator{node};
}

template <class T> list<T>::iterator list<T>::erase(iterator position) {
  if (empty() || position == end())
    return end();

  Node *prev_elem = get_prev_node(as_node(position));
  prev_elem->next = as_node(position)->next;
  if (as_node(position) == first)
    first = as_node(position)->next;
  delete as_node(position);
  --list_size;
  return iterator(prev_elem->next);
}

template <class T> void list<T>::clear() {
  if (list_size == 0)
    return;

  if (list_size == 1)
    delete first;

  for (Node *node = first; node != last;) {
    auto del = node;
    node = node->next;
    delete del;
  }

  first = nullptr;
}
