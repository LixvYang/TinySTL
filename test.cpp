#include <iostream>
#include "TinySTL/vector.h"

int main()
{
  tinystl::vector<int> v1;
  v1.push_back(10);
  std::cout << *v1.begin() << std::endl;

  return 0;
}