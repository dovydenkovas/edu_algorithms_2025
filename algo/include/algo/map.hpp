#pragma once
#include <algorithm>
#include <ctype.h>
#include <exception>
#include <iostream>
#include <stdexcept>

namespace algo {
template <class K, class V> class map {

public:
  explicit map();
  explicit map(map &other);
  map &operator=(map &other);

  V &operator[](K key);
  V const &operator[](K key) const;

  size_t size();
  bool empty();
  void clear();

  bool contains(K key) const;
  void insert(K key, V value);
  void erase(K key);

  class iterator;
  iterator begin();
  iterator end();

  ~map();

private:
  struct Node {
    std::pair<const K, V> data;
    Node *parent;
    Node *left;
    Node *right;
  };

  Node *root;
  Node *next_node(Node *prev);
  Node *get(K key) const;
  size_t tree_size;
};

template <class K, class V> class map<K, V>::iterator {
private:
  Node *node;
  bool is_end;

public:
  explicit iterator(Node *n, bool is_end_) : node(n), is_end(is_end_) {}

  // Выбор следующего по величине ключа.
  iterator &operator++() {
    if (is_end)
      return *this;
    // Пример обхода следующий:
    //       D         |
    //     /   \       |
    //    B     F      |
    //   / \   / \     |
    //  A   C E   G    |
    // Если есть правая ветвь - следующий элемент минимальный в ней.
    // Например, потомки элементов B, D, F.
    if (node->right) {
      node = node->right;
      while (node->left)
        node = node->left;
      return *this;
    }
    // Если элемент - левый потомок, следующий элемент - его родитель.
    // Например, потомки элементов A, E.
    if (node->parent && node->parent->left == node) {
      node = node->parent;
      return *this;
    }
    // Если элемент - правый потомок, следующий элемент - первый элемент,
    // содержащий предшественника в левой ветви. Пример: после C идет D.
    Node *next = node;
    while (next->parent && next->parent->right == next)
      next = next->parent;
    // Если предшественник был в левой ветви, следующий элемент - родитель,
    // иначе обход окончен если в результате поиска достигли корня,
    // поднимаясь по правой ветви - обход окончен.
    if (next->parent)
      node = next->parent;
    else
      is_end = true;
    return *this;
  }

  iterator operator++(int) {
    iterator retval = *this;
    ++(*this);
    return retval;
  }

  bool operator==(iterator other) const {
    return node == other.node && is_end == other.is_end;
  }
  bool operator!=(iterator other) const { return !(*this == other); }
  std::pair<const K, V> &operator*() const { return this->node->data; }
};

template <class K, class V> map<K, V>::map() : root{nullptr}, tree_size{0} {}

template <class K, class V>
map<K, V>::map(map &other) : root{nullptr}, tree_size{0} {
  *this = other;
}

template <class K, class V> map<K, V> &map<K, V>::operator=(map &other) {
  clear();
  for (auto &p : other)
    insert(p.first, p.second);
  return *this;
}

// Выбор следующего по величине ключа.
template <class K, class V>
typename map<K, V>::Node *map<K, V>::next_node(typename map<K, V>::Node *node) {
  // Пример обхода следующий:
  //       D          //
  //     /   \        //
  //    B     F       //
  //   / \   / \      //
  //  A   C E   G     //
  // Если есть правая ветвь - следующий элемент минимальный в ней.
  // Например, потомки элементов B, D, F.
  if (node->right) {
    node = node->right;
    while (node->left)
      node = node->left;
    return node;
  }
  // Если элемент - левый потомок, следующий элемент - его родитель.
  // Например, потомки элементов A, E.
  if (node->parent && node->parent->left == node) {
    return node->parent;
  }
  // Если элемент - правый потомок, следующий элемент - первый элемент,
  // содержащий предшественника в левой ветви. Пример: после C идет D.
  Node *next = node;
  while (next->parent && next->parent->right == next)
    next = next->parent;
  // Если предшественник был в левой ветви, следующий элемент - родитель,
  // иначе обход окончен если в результате поиска достигли корня,
  // поднимаясь по правой ветви - обход окончен.
  if (next->parent)
    return next->parent;
  return node;
}

// Возвращает указатель на узел, соответствующий
// искомому ключу или nullptr.
template <class K, class V>
typename map<K, V>::Node *map<K, V>::get(K key) const {
  Node *node = root;
  while (node)
    if (node->data.first == key)
      return node;
    else if (key < node->data.first)
      node = node->left;
    else
      node = node->right;
  return nullptr;
}

// Возвращает значение по ключу.
// Если ключа нет - вызывает исключение.
template <class K, class V> V &map<K, V>::operator[](K key) {
  Node *node = get(key);
  if (node)
    return node->data.second;
  throw std::runtime_error("Key not found");
}

// Возвращает значение по ключу.
// Если ключа нет - вызывает исключение.
template <class K, class V> V const &map<K, V>::operator[](K key) const {
  Node *node = get(key);
  if (node)
    return node->data.second;
  throw std::runtime_error("Key not found");
}

// Возвращает количество ключей в дереве.
template <class K, class V> size_t map<K, V>::size() { return tree_size; }

// Возвращает true, если дерево не содержит ключей.
template <class K, class V> bool map<K, V>::empty() { return tree_size == 0; }

// Возвращает true, если ключ есть в дереве.
template <class K, class V> bool map<K, V>::contains(K key) const {
  Node *node = get(key);
  return node != nullptr;
}

// Добавляет пару ключ-значение в дерево.
// Если ключ уже добавлен - вызывает исключение.
template <class K, class V> void map<K, V>::insert(K key, V value) {
  Node *new_node = new Node{{key, value}, nullptr, nullptr, nullptr};
  // Поиск места нового элемента
  if (!root) {
    tree_size = 1;
    root = new_node;
    return;
  }
  Node *node = root;
  Node *parent = nullptr;
  while (node) {
    parent = node;
    if (node->data.first == key) {
      delete new_node;
      throw std::runtime_error("Inserted key already exist.");
    }
    else if (key < node->data.first)
      node = node->left;
    else
      node = node->right;
  }
  // Вставка нового листа
  ++tree_size;
  new_node->parent = parent;
  if (key < parent->data.first)
    parent->left = new_node;
  else
    parent->right = new_node;
  // Балансировка
}

// Удаляет пару ключ-значение из дерева.
// Если ключа нет - вызывает исключение.
template <class K, class V> void map<K, V>::erase(K key) {
  Node *node = get(key);
  if (!node)
    throw std::runtime_error("Key not found");

  // Взять следующий по величине элемент
  Node *next = next_node(node);
  // Если элемент максимален
  if (next == node) {
    // Заменить удаляемый элемент его левым потомком.
    if (!next->parent)
      root = next->left;
    else {
      next->parent->right = next->left;
      if (next->right)
        next->right->parent = next->parent;
    }
  } else {
    if (!next->parent)
      root = next->left;
    else if (next->parent->left == next) {
      next->parent->left = next->left;
      if (next->left)
        next->left->parent = next->parent;
    } else {
      next->parent->right = next->right;
      if (next->right)
        next->right->parent = next->parent;
    }
    // Заменить удаляемый элемент следующим по величине.
    if (!node->parent)
      root = next;
    else if (node->parent->left == node)
      node->parent->left = next;
    else
      node->parent->right = next;
    next->right = node->right;
    if (node->right)
      node->right->parent = next;
    next->left = node->left;
    if (node->left)
      node->left->parent = next;
  }

  next->parent = node->parent;
  delete node;
  --tree_size;

  // Балансировка
}

// Выбор минимального элемента.
template <class K, class V> typename map<K, V>::iterator map<K, V>::begin() {
  if (!root)
    return end();

  Node *node = root;
  while (node->left)
    node = node->left;
  return iterator{node, false};
}

template <class K, class V> typename map<K, V>::iterator map<K, V>::end() {
  if (!root)
    return iterator(nullptr, true);

  Node *node = root;
  while (node->right)
    node = node->right;
  return iterator{node, true};
}

// Удалить все узлы дерева.
template <class K, class V> void map<K, V>::clear() {
  while (size())
    erase((*begin()).first);
}

template <class K, class V> map<K, V>::~map() {
 clear();
}

}; // namespace algo
