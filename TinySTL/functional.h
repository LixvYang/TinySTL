#ifndef TINYSTL_FUNCTIONAL_H_
#define TINYSTL_FUNCTIONAL_H_

// 这个头文件包含了 tinystl 的函数对象与哈希函数
#include <cstddef>

namespace tinystl
{

  // 定义二元函数的参数型别的返回值型别
  template <class Arg1, class Arg2, class Result>
  struct binary_function
  {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
  };

  // 函数对象：小于
  template <class T>
  struct less : public binary_function<T, T, bool>
  {
    bool operator()(const T &x, const T &y) const { return x < y; }
  };

} // namespace tinystl

#endif // !TINYSTL_FUNCTIONAL_H_