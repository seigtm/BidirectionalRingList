#pragma once

#include <cassert> // To emergency escape programm.

// Doubly connected ring list class.
class RingList
{
  using size_t = unsigned long long;
  using value_t = double;

  // List node structure.
  struct Node
  {
    // Constructor
    Node(const value_t value = 0);

    value_t data;   // Node data.
    Node *next;     // Next node pointer.
    Node *previous; // Previous node pointer.
  };

public:
  using Iterator = Node *;

  struct Node_Iterator
  {
    Node_Iterator(Node *node);

    Node *current; // Current Node pointer.

    // Overloading operators n++, n--, n == o and n != o.
    Node_Iterator operator++(int);
    Node_Iterator operator--(int);
    bool operator==(const Node_Iterator &other);
    bool operator!=(const Node_Iterator &other);
  };

  RingList();
  RingList(const size_t size, const value_t value = 0);
  explicit RingList(const RingList &other);
  ~RingList();

  // Overloading operator = for lists.
  // Assigns new contents to the list, replacing its current
  // contents, and modifying its size accordingly.
  RingList &operator=(const RingList &other);

  Iterator push_back(const value_t value);  // Adds a new element at the end.
  Iterator push_front(const value_t value); // Inserts a new element at the beginning.

  // Inserts new element(-s) before the element at the specified position.
  Iterator insert(const size_t position,
                  const value_t value);
  Iterator insert(const size_t position,
                  const RingList &list);

  // Resizes the list so that it contains n elements.
  size_t resize(const size_t newSize,
                const value_t default_value = 0);

  // Removes element(-s) at the specified position (or gap).
  void remove(const size_t position);
  void remove(const size_t start_pos,
              const size_t end_pos);

  // Returns the data of the element at position n.
  value_t at(const size_t position) const;

  // Removes all elements from the list (which are destroyed),
  // leaving it with a size of 0.
  size_t clear();

  size_t size() const;    // Returns the number of elements in the list.
  Iterator begin() const; // Returns an iterator pointing to the first element in the list.
  Iterator end() const;   // Returns an iterator pointing to the last element in the list.

private:
  size_t m_size; // The number of elements in the list.
  Node *head;    // List first element pointer aka "head".

  // Creates first list element aka "head".
  Iterator createHead(const value_t value);
  // Returns the reference to the element at position n.
  Iterator find(const size_t position) const;

  // Clears the memory from the node(-s).
  void clearMemory(const Iterator removable);
  void clearMemory(const Iterator begin,
                   const Iterator end);
};
