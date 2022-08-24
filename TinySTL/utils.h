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

  // swap

  template <class Tp>
  void swap(Tp &lhs, Tp &rhs)
  {
    auto tmp(tinystl::move(lhs));
    lhs = tinystl::move(rhs);
    rhs = tinystl::move(tmp);
  }

  template <class ForwardIter1, class ForwardIter2>
  ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2)
  {
    for (; first1 != last1; ++first1, (void)++first2)
      tinystl::swap(*first1, *first2);
    return first2;
  }

  template <class Tp, size_t N>
  void swap(Tp (&a)[N], Tp (&b)[N])
  {
    tinystl::swap_range(a, a + N, b);
  }

  // 全局函数，让两个数据成为一个 pair
  template <class Ty1, class Ty2>
  pair<Ty1, Ty2> make_pair(Ty1 &&first, Ty2 &&second)
  {
    return pair<Ty1, Ty2>(tinystl::forward<Ty1>(first), tinystl::forward<Ty2>(second));
  }

} // namespace tinystl

#endif // !TINYSTL_UTILS_H_