#ifndef TINYSTL_UTILS_H_
#define TINYSTL_UTILS_H_

// 这个文件包括一些通用工具， 包括move, forward, swap 等函数， 以及pair 等
#include <cstddef>
#include "type_traits.h"

namespace tinystl
{
  // move
  template <class T>
  typename std::remove_reference<T>::type &&move(T &&arg) noexcept
  {
    return static_cast<typename std::remove_reference<T>::type &&>(arg);
  }

  // forward
  template <class T>
  T &&forward(typename std::remove_reference<T>::type &arg) noexcept
  {
    return static_cast<T &&>(arg);
  }

  template <class T>
  T &&forward(typename std::remove_reference<T>::type &&arg) noexcept
  {
    static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
    return static_cast<T &&>(arg);
  }

} // namespace tinystl

#endif // !TINYSTL_UTILS_H_