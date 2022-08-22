#include "../TinySTL/stack.h"
#include <iostream>

using namespace tinystl;

int main()
{
  stack<int> s1;
  for (int i = 0; i < 10; i++)
  {
    s1.push(i);
  }
  s1.pop();
  s1.empty();
  std::cout << !s1.empty() << std::endl;
  std::cout << s1.top() << std::endl;
  s1.clear();
  return 0;
}
