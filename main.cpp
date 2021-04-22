#include <iostream>
#include <chrono> // To count the time.

#include "RingList.h" // Including doubly connected ring list class.

void showList(const RingList &list); // Shows all elements from the list.

void showListWithIterators(const RingList &list); // showList(), but uses iterators.

// Main function.
int main()
{
  std::cout << "push_front():\n\n";
  std::cout << "x100: ";
  RingList list;
  auto start = std::chrono::system_clock::now();

  for (size_t i{}; i < 100; ++i)
    list.push_front(i);

  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "\t\tElapsed time: " << elapsed.count() << "s\n";
  std::cout << "x10'000: ";
  {
    RingList list;
    auto start = std::chrono::system_clock::now();

    for (size_t i{}; i < 10'000; ++i)
      list.push_front(i);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\tElapsed time: " << elapsed.count() << "s\n";
  }
  std::cout << "x1'000'000: ";
  {
    RingList list;
    auto start = std::chrono::system_clock::now();

    for (size_t i{}; i < 1'000'000; ++i)
      list.push_front(i);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\tElapsed time: " << elapsed.count() << "s\n";
  }

  std::cout << "\n\npush_back():\n\n";
  std::cout << "x100: ";
  {
    RingList list;
    auto start = std::chrono::system_clock::now();

    for (size_t i{}; i < 100; ++i)
      list.push_back(i);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\t\tElapsed time: " << elapsed.count() << "s\n";
  }
  std::cout << "x10'000: ";
  {
    RingList list;
    auto start = std::chrono::system_clock::now();

    for (size_t i{}; i < 10'000; ++i)
      list.push_back(i);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\tElapsed time: " << elapsed.count() << "s\n";
  }
  std::cout << "x1'000'000: ";
  {
    RingList list;
    auto start = std::chrono::system_clock::now();

    for (size_t i{}; i < 1'000'000; ++i)
      list.push_back(i);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\tElapsed time: " << elapsed.count() << "s\n";
  }

  std::cout << "\n\nremove(0):\n\n";
  std::cout << "x100: ";
  {
    RingList list{100};
    auto start = std::chrono::system_clock::now();

    for (size_t i{}; i < 100; ++i)
      list.remove(0);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\t\tElapsed time: " << elapsed.count() << "s\n";
  }
  std::cout << "x10'000: ";
  {
    RingList list{10'000};
    auto start = std::chrono::system_clock::now();

    for (size_t i{}; i < 10'000; ++i)
      list.remove(0);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\tElapsed time: " << elapsed.count() << "s\n";
  }
  std::cout << "x1'000'000: ";
  {
    RingList list{1'000'000};
    auto start = std::chrono::system_clock::now();

    for (size_t i{}; i < 1'000'000; ++i)
      list.remove(0);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\tElapsed time: " << elapsed.count() << "s\n";
  }

  std::cout << "\n\nat(0):\n\n";
  std::cout << "x100: ";
  {
    RingList list{100};
    auto start = std::chrono::system_clock::now();

    for (size_t i{}; i < 100; ++i)
      list.at(0);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\t\tElapsed time: " << elapsed.count() << "s\n";
  }
  std::cout << "x10'000: ";
  {
    RingList list{10'000};
    auto start = std::chrono::system_clock::now();

    for (size_t i{}; i < 10'000; ++i)
      list.at(0);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\tElapsed time: " << elapsed.count() << "s\n";
  }
  std::cout << "x1'000'000: ";
  {
    RingList list{1'000'000};
    auto start = std::chrono::system_clock::now();

    for (size_t i{}; i < 1'000'000; ++i)
      list.at(0);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\tElapsed time: " << elapsed.count() << "s\n";
  }

  std::cout << "\n\nremove(middle):\n\n";
  std::cout << "x100 (middle = 49): ";
  {
    RingList list{1'000'000};
    auto start = std::chrono::system_clock::now();

    for (size_t i{}; i < 100; ++i)
      list.remove(49);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\t\tElapsed time: " << elapsed.count() << "s\n";
  }
  std::cout << "x10'000 (middle = 4'999): ";
  {
    RingList list{1'000'000};
    auto start = std::chrono::system_clock::now();

    for (size_t i{}; i < 10'000; ++i)
      list.remove(4'999);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\tElapsed time: " << elapsed.count() << "s\n";
  }

  std::cout << "\n\nat(middle):\n\n";
  std::cout << "x100 (middle = 49): ";
  {
    RingList list{100};
    auto start = std::chrono::system_clock::now();

    for (size_t i{}; i < 100; ++i)
      list.at(49);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\t\tElapsed time: " << elapsed.count() << "s\n";
  }
  std::cout << "x10'000 (middle = 4'999): ";
  {
    RingList list{10'000};
    auto start = std::chrono::system_clock::now();

    for (size_t i{}; i < 10'000; ++i)
      list.at(4'999);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\tElapsed time: " << elapsed.count() << "s\n";
  }
}

void showList(const RingList &list)
{
  for (size_t i{}; i < list.size(); ++i)
    std::cout << list.at(i) << ' ';

  std::cout << "\nList size = "
            << list.size()
            << "\n\n";
}

void showListWithIterators(const RingList &list)
{
  RingList::Node_Iterator it{list.begin()};

  do
  {
    std::cout << it.current->data << ' ';
    it++;
  } while (it != list.begin());
};
