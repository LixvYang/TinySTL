#include "TinySTL/vector.h"
#include <iostream>
using namespace tinystl;

void printVector(tinystl::vector<int> &v)
{
  for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
  {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

int main()
{
  vector<int> v1;
  v1.push_back(1);
  // for (int i = 0; i < 10; i++)
  // {
  //   v1.push_back(i);
  // }
  // printVector(v1);
  // v1.resize(5);
  // printVector(v1);
  // v1.resize(15, 100);
  printVector(v1);

  return 0;
}