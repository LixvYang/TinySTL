#include <iostream>
#include "../TinySTL/set.h"

// template <class T>
// void printset(tinystl::set<T> d1)
// {
//   for (tinystl::set<int>::iterator it = d1.begin(); it != d1.end(); it++)
//   {
//     std::cout << *it << " ";
//   }
// }

int main()
{
  tinystl::set<int> s;
  s.insert(1);
  return 0;
}