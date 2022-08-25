#include <iostream>
#include "../TinySTL/map.h"

using namespace tinystl;

int main()
{
  map<int, int> m;
  m.insert(make_pair(10, 10));
  std::cout << m.empty() << std::endl;
  return 0;
}