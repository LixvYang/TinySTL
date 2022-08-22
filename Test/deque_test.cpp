#include <iostream>
#include "../TinySTL/deque.h"

template <class T>
void printDeque(tinystl::deque<T> d1)
{
  for (tinystl::deque<int>::iterator it = d1.begin(); it != d1.end(); it++)
  {
    std::cout << *it << " ";
  }
}

int main()
{
  tinystl::deque<int32_t> d1;
  for (int i = 0; i < 10; i++)
  {
    d1.push_back(i);
  }
  d1.pop_back();
  tinystl::deque<int>::iterator it = d1.begin();
  it++;
  std::cout << ++*it << std::endl;
  *it = 10;
  d1.pop_front();
  d1.erase(it);
  std::cout << d1.front() << std::endl;
  for (tinystl::deque<int>::const_iterator it = d1.begin(); it != d1.end(); it++)
  {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
  // printDeque<int>(d1);
  return 0;
}