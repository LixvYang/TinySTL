#include <iostream>
#include "../TinySTL/vector.h"

void printVector(tinystl::vector<int> v1)
{
  for (tinystl::vector<int>::const_iterator it = v1.begin(); it != v1.end(); it++)
  {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

int main()
{
  tinystl::vector<int> v1;
  for (int i = 0; i < 10; i++)
  {
    v1.push_back(i);
  }
  printVector(v1);

  return 0;
}