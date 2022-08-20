#include <iostream>
#include "../TinySTL/list.h"

void printList(tinystl::list<int> l1)
{
  for (tinystl::list<int>::const_iterator it = l1.begin(); it != l1.end(); it++)
  {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

int main()
{
  tinystl::list<int> l1;
  for (int i = 0; i < 10; i++)
  {
    l1.push_back(i);
  }
  printList(l1);
  return 0;
}