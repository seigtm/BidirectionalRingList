#include "RingList.h"

RingList::RingList()
    : m_size{0},
      head{nullptr}
{
}

RingList::RingList(const size_t size, const value_t value)
    : m_size{0},
      head{nullptr}

{
  resize(size, value); // Will fill the list with some value and resize it.
}

RingList::RingList(const RingList &other)
    : m_size{0},
      head{nullptr}

{
  *this = other; // Copies everything from other list.
}

RingList::~RingList()
{
  clear();
}

RingList &RingList::operator=(const RingList &other)
{
  // Resize() returnes list size, so if this size > 0.
  if (resize(other.size()))
  {
    Node_Iterator currentNode(head);
    Node_Iterator currentOtherNode(other.head);

    for (size_t current_id{}; m_size > current_id; ++current_id)
    {
      // Copying data between lists.
      currentNode.current->data = currentOtherNode.current->data;
      currentNode++;      // Moving the pointer in this list.
      currentOtherNode++; // Moving the pointer in other list.
    }
  }
  return *this;
}

RingList::Node::Node(const value_t value)
    : data{value},
      next{nullptr},
      previous{nullptr}
{
}

RingList::Iterator RingList::createHead(const value_t value)
{
  head = new Node(value); // Creates the first new node with some value.

  // Makes it point to itself.
  head->previous = head;
  head->next = head;

  return head;
}

RingList::Iterator RingList::push_back(const value_t value)
{
  ++m_size;

  if (nullptr == head)
  {                           // If head is not created.
    return createHead(value); // Creates it.
  }

  Iterator tailNode = head->previous; // Pointer to the last node aka tail.
  tailNode->next = new Node(value);   // Creates new node after it.
  Iterator newNode = tailNode->next;  // Pointer to the new node.

  // Links new node with head and tail.
  newNode->next = head;
  newNode->previous = tailNode;
  head->previous = newNode;

  return newNode;
}

RingList::Iterator RingList::push_front(const value_t value)
{
  ++m_size;

  if (nullptr == head)        // If head is not created.
    return createHead(value); // Creates it.

  Iterator tailNode = head->previous; // Pointer to the last node aka tail.
  head->previous = new Node(value);   // Creates new node before the first one aka head.
  Iterator newNode = head->previous;  // Pointer to the new node.

  // Links new node with head and tail.
  newNode->previous = tailNode;
  newNode->next = head;
  tailNode->next = newNode;

  head = newNode; // Push front, so new node is now list's head.

  return newNode;
}

RingList::Iterator
RingList::insert(const size_t position, const value_t value)
{
  if (0 == position) // insert(0) == push_front().
    return push_front(value);

  Iterator currentNode = find(position);         // Pointer to the node at some position.
  Iterator previousNode = currentNode->previous; // Pointer to the node before it.

  previousNode->next = new Node(value);  // Creates new node after this.
  Iterator newNode = previousNode->next; // Pointer to the new node.

  // Links new node with the list.
  currentNode->previous = newNode;
  newNode->next = currentNode;
  newNode->previous = previousNode;

  ++m_size;

  return newNode;
}

RingList::Iterator
RingList::insert(const size_t position, const RingList &list)
{
  if (0 == list.size()) // We don't need to insert empty lists.
    return nullptr;

  if (1 == list.size()) // We already have insert() for one data.
    return insert(position, list.head->data);

  // To check if user trying to insert other list in this
  // empty one to out of range position.
  bool isInRange{0 == m_size && position > 0};
  assert(!isInRange && "list index out of range");

  if (0 == m_size)
  {               // If this list is empty.
    *this = list; // Just copy other list in this list.
    return head;
  }

  m_size += list.size(); // Increase size to the other's list size.

  Iterator endNode = find(position);        // Pointer to this list's node at some position.
  Iterator currentNode = endNode->previous; // Pointer to the node before it.
  Iterator newNode{nullptr};                // Pointer for new nodes.
  Iterator otherPosition = list.begin();    // Pointer to the other list's first node aka head.

  for (size_t i{}; i < list.size(); ++i)
  {
    currentNode->next = new Node(otherPosition->data); // Creates new node after current node pointer.
    newNode = currentNode->next;                       // Moves this pointer to the new node.
    newNode->previous = currentNode;                   // Links it with the node before it.
    currentNode = newNode;                             // Moves current node pointer.
    otherPosition = otherPosition->next;               // Moves pointer in the other list.
  }
  // Links new node with the list.
  currentNode->next = endNode;
  endNode->previous = currentNode;

  return endNode;
}

RingList::Iterator RingList::begin() const
{
  return head; // Returns list's first element aka head.
}

RingList::Iterator RingList::end() const
{
  return head->previous; // Returns list's last element aka tail.
}

RingList::size_t
RingList::resize(const size_t newSize, const value_t default_value)
{
  if (m_size == newSize) // There is no point in changing the size.
    return m_size;

  if (0 == newSize) // Resize(0) == clear().
    return clear();

  // If it's bigger, then increase.
  if (m_size < newSize)
  {

    for (size_t currentID{0}, increaseAmount{newSize - m_size};
         increaseAmount > currentID; ++currentID)

      push_back(default_value);
  }
  // If it's smaller, then destroy nodes and clear memory.
  else
  {
    clearMemory(find(newSize), head->previous);
    m_size = newSize;
  }

  return m_size;
}

void RingList::remove(const RingList::size_t position)
{
  Iterator removableNode = find(position); // Pointer to the removing node.

  if (0 == position)   // If removing head:
    head = head->next; // change head.

  clearMemory(removableNode);
}

void RingList::remove(const RingList::size_t begin,
                      const RingList::size_t end)
{
  if (begin == end) // We already have remove() for one node.
    return remove(begin);

  Iterator beginIT{nullptr}, endIT{nullptr};
  size_t gap{}; // The gap between begin and end.

  // To remove nodes forwards.
  if (end > begin)
  {
    beginIT = find(begin); // Pointer to the first removing node.
    endIT = find(end);     // Pointer to the last removing node.
    gap = end - begin + 1;
  }
  // To remove nodes backwards.
  else
  {
    beginIT = find(end); // Pointer to the first removing node.
    endIT = find(begin); // Pointer to the last removing node.
    gap = begin - end + 1;
  }
  if (0 == begin) // To change the head if starts with it.
    head = endIT->next;

  clearMemory(beginIT, endIT);

  m_size -= gap;
}

RingList::size_t RingList::clear()
{
  if (m_size != 0) // We don't need to clear memory if our list is empty.
    clearMemory(head, head->previous);

  head = nullptr;
  m_size = 0;

  return m_size;
}

size_t RingList::size() const
{
  return m_size;
}

RingList::Iterator RingList::find(const size_t position) const
{
  // Check for incorrect position index (OFR).
  assert(m_size > position && "list index out of range");

  Node_Iterator foundNode(head);

  if (0 == position) // Node at 0 == head
    return head;

  // If second half (or in the middle).
  if (position >= m_size / 2)
  {
    for (size_t currentID{}; currentID < m_size - position; ++currentID)
    {
      foundNode--;
    }
  }
  // If first half.
  else
  {
    for (size_t currentID{}; currentID < position; ++currentID)
    {
      foundNode++;
    }
  }
  return foundNode.current;
}

void RingList::clearMemory(const RingList::Iterator removable)
{
  Iterator previousNode = removable->previous; // Node before removable.
  Iterator nextNode = removable->next;         // Node after removable.

  // Change links.
  previousNode->next = nextNode;
  nextNode->previous = previousNode;

  --m_size;

  if (0 == m_size)
    head = nullptr;

  delete removable;
}

void RingList::clearMemory(const Iterator begin,
                           const Iterator end)
{
  if (begin == end) // We already have clearMemory() for one node.
    clearMemory(begin);

  else
  {
    Iterator previous = begin->previous; // Node before removables.
    Iterator next = end->next;           // Node after removables.

    // Iterators for cycling removal.
    Iterator current = begin;
    Iterator temp = current;

    while (current != next)
    {
      temp = current->next;
      delete current;
      current = temp;
    }

    // Change links.
    previous->next = next;
    next->previous = previous;
  }
}

RingList::value_t RingList::at(const RingList::size_t position) const
{
  return find(position)->data;
}

RingList::Node_Iterator::Node_Iterator(RingList::Node *node)
    : current{node}
{
}

RingList::Node_Iterator RingList::Node_Iterator::operator++(int)
{
  current = current->next;
  return *this;
}

RingList::Node_Iterator RingList::Node_Iterator::operator--(int)
{
  current = current->previous;
  return *this;
}

bool RingList::Node_Iterator::operator==(const Node_Iterator &other)
{
  return this->current == other.current;
}

bool RingList::Node_Iterator::operator!=(const RingList::Node_Iterator &other)
{
  return this->current != other.current;
}
