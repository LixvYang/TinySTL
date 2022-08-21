#include <iostream>
#include "../TinySTL/deque.h"

void printDeque(tinystl::deque<int> d1)
{
  for (tinystl::deque<int>::const_iterator it = d1.begin(); it != d1.end(); it++)
  {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

int main()
{
  tinystl::deque<int> d1;
  for (int i = 0; i < 10; i++)
  {
    d1.push_back(i);
  }
  printDeque(d1);
  return 0;
}