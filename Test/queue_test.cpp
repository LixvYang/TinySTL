#include "../TinySTL/queue.h"
#include <iostream>

using namespace tinystl;

int main()
{
  queue<int> q1;
  for (int i = 0; i < 10; i++)
  {
    q1.push(i);
  }
  q1.pop();
  q1.empty();
  std::cout << !q1.empty() << std::endl;
  std::cout << q1.back() << std::endl;
  q1.clear();
  return 0;
}
