#pragma once
#include <algorithm>
#include <iostream>
#include <algo/vector.hpp>
#include <math.h>
#include <stdexcept>
#include <vector>

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

  ~map();

  std::vector<V> forward();
  int height();

private:
  struct Node {
    std::pair<const K, V> data;
    Node *parent;
    Node *left;
    Node *right;
    int bf = 0;
  };

  Node* right_rotate(Node *node);
  Node* left_rotate(Node *node);
  Node* big_right_rotate(Node *node);
  Node* big_left_rotate(Node *node);
  void balance(Node *node);
  void balance_after_remove(Node* node);
  Node *root;
  Node *next_node(Node *prev);
  Node *get(K key) const;
  size_t tree_size;
  void rec_forward(Node *node, std::vector<V> &res);
  int rec_height(Node *node);
  void move(Node* node, Node* position);
  Node *minimum(Node *node);
  Node *rotate(Node *node);
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
  balance(new_node);
}

// Удаляет пару ключ-значение из дерева.
// Если ключа нет - вызывает исключение.
template <class K, class V> void map<K, V>::erase(K key) {
  Node *node = get(key);
  if (!node)
    throw std::runtime_error("Key not found");

  if (!node->left) {
    // Если нет левого поддерева, ставим на место удаляемого элемента правое поддерево
    if (node->parent) {
      if (node->parent->left == node)
        --node->parent->bf;
      else
        ++node->parent->bf;
    }
    move(node->right, node);
    balance_after_remove(node->parent);

  } else if (!node->right) {
    // Если нет правого поддерева, ставим на место удаляемого левое поддерево
    if (node->parent) {
      if (node->parent->left == node)
        --node->parent->bf;
      else
        ++node->parent->bf;
    }
    move(node->left, node);
    balance_after_remove(node->parent);

  } else {
    // Есть оба поддерева?
    // Взять следующий по величине элемент
    Node *next = minimum(node->right);
    Node *balanced = next;
    if (next->parent != node) {
      balanced = next->parent;
      --balanced->bf;
      move(next->right, next);
      next->right = node->right;
      next->right->parent = next;
    } else {
      next->bf = node->bf + 1;
    }
    move(next, node);
    next->left = node->left;
    next->left->parent = next;
    balance_after_remove(balanced);
    }

    delete node;
    --tree_size;
}


// Удалить все узлы дерева.
template <class K, class V> void map<K, V>::clear() {
  while (root)
    erase(root->data.first);
}

template <class K, class V> map<K, V>::~map() {
 clear();
}

template <class K, class V> typename map<K, V>::Node* map<K, V>::right_rotate(Node *b) {
  // Перемещаем правого потомка на место родителя
  Node *a = b->right;
  move(a, b);

  // Левый потомок правого потомка node становится правым потомком node
  b->right = a->left;
  if (b->right)
    b->right->parent = b;

  // Подключаем node к b
  b->parent = a;
  a->left = b;

  return a;
}

template <class K, class V> typename map<K, V>::Node* map<K, V>::left_rotate(Node *b) {
  // Перемещаем левого потомка на место родителя
  Node *a = b->left;
  move(a, b);

  // Правый потомок левого потомка node становится левым потомком node
  b->left = a->right;
  if (b->left)
    b->left->parent = b;

  // Подключаем node к a
  b->parent = a;
  a->right = b;

  return a;
}

template <class K, class V> typename map<K, V>::Node* map<K, V>::big_right_rotate(Node *node) {
  left_rotate(node->right);
  return right_rotate(node);
}

template <class K, class V> typename map<K, V>::Node* map<K, V>::big_left_rotate(Node *node) {
  right_rotate(node->left);
  return left_rotate(node);
}

template <class K, class V> typename map<K, V>::Node *map<K, V>::rotate(Node *node) {
  if (node->bf == -2 && node->right->bf == -1) {
    node->bf = 0;
    node->right->bf = 0;
    node = right_rotate(node);
  } else if (node->bf == -2 && node->right->bf == 0) {
    node->bf = -1;
    node->right->bf = 1;
    node = right_rotate(node);

  } else if (node->bf == 2 && node->left->bf == 1) {
    node->bf = 0;
    node->left->bf = 0;
    node = left_rotate(node) ;
  } else if (node->bf == 2 && node->left->bf == 0) {
    node->bf = 1;
    node->left->bf = -1;
    node = left_rotate(node);

  } else if (node->bf == -2 && node->right->bf == 1 && node->right->left->bf == 1) {
    node->bf = 0;
    node->right->bf = -1;
    node->right->left->bf = 0;
    node = big_right_rotate(node);
  } else if (node->bf == -2 && node->right->bf == 1 && node->right->left->bf == -1) {
    node->bf = 1;
    node->right->bf = 0;
    node->right->left->bf = 0;
    node = big_right_rotate(node);
  } else if (node->bf == -2 && node->right->bf == 1 && node->right->left->bf == 0) {
    node->bf = 0;
    node->right->bf = 0;
    node->right->left->bf = 0;
    node = big_right_rotate(node);

  } else if (node->bf == 2 && node->left->bf == -1 && node->left->right->bf == -1) {
    node->bf = 0;
    node->left->bf = 1;
    node->left->right->bf = 0;
    node = big_left_rotate(node);
  } else if (node->bf == 2 && node->left->bf == -1 && node->left->right->bf == 1) {
    node->bf = -1;
    node->left->bf = 0;
    node->left->right->bf = 0;
    node = big_left_rotate(node);
  } else if (node->bf == 2 && node->left->bf == -1 && node->left->right->bf == 1) {
    node->bf = 0;
    node->left->bf = 0;
    node->left->right->bf = 0;
    node = big_left_rotate(node);
  }
 return node;
}


template <class K, class V> void map<K, V>::balance(Node *node) {
  if (!node)
    std::cerr << "NULL balanced node";

  Node *prev = node;
  node = node->parent;
  while (node) { // Поднимаемся до корня
    if (node->left == prev)
      ++node->bf;
    else
      --node->bf;

    if (node->bf == 0) // Если вершина сбалансирована останавливаем подъем
      return;

    // Если баланс-фактор +-1 - продолжаем подъем
    // Если баланс-фактор +-2 - выполняем поворот
    if (abs(node->bf) != 1)
     node = rotate(node);

    if (node->bf == 0) // Если вершина сбалансирована останавливаем подъем
      return;

    prev = node;
    node = node->parent;
  }
}

template <class K, class V> void map<K, V>::balance_after_remove(Node *node) {
  if (!node)
    return;

  Node *prev = node;
  while (node) { // Поднимаемся до корня
    if (node->bf == 0) // Если вершина сбалансирована останавливаем подъем
      return;

    // Если баланс-фактор +-1 - продолжаем подъем
    // Если баланс-фактор +-2 - выполняем поворот
    if (abs(node->bf) != 1)
      node = rotate(node);

    if (!node || node->bf == 0) // Если вершина сбалансирована останавливаем подъем
      return;

    if (node->left == prev)
      --node->bf;
    else
      ++node->bf;

    prev = node;
    if (!node->parent)
         return;
    node = node->parent;
  }
}

template <class K, class V> std::vector<V> map<K, V>::forward() {
  std::vector<V> vec;
  rec_forward(root, vec);
  return vec;
}

template <class K, class V> void map<K, V>::rec_forward(Node *node, std::vector<V> &res) {
  if (!node)
    return;
  res.push_back(node->data.second);
  rec_forward(node->left, res);
  rec_forward(node->right, res);
}

template <class K, class V> int map<K, V>::rec_height(Node *node) {
  if (!node)
    return 0;
  return 1 + std::max(rec_height(node->left), rec_height(node->right));
}

template <class K, class V> int map<K, V>::height() {
  return rec_height(root);
}

template <class K, class V> void map<K, V>::move(Node *node, Node *position) {
  if (position->parent) {
    if (position->parent->left == position)
      position->parent->left = node;
    else
      position->parent->right = node;
  } else {
    root = node;
  }
  if (node)
    node->parent = position->parent;
}

template <class K, class V> typename map<K, V>::Node * map<K, V>::minimum(Node *node) {
  while (node->left)
    node = node->left;
  return node;
}


}; // namespace algo
