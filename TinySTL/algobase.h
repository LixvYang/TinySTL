#ifndef TINYSTL_ALGOBASE_H_
#define TINYSTL_ALGOBASE_H_

#include <cstring>
#include "iterator.h"
#include "utils.h"

namespace tinystl
{

  /*****************************************************************************************/
  // max
  // 取二者中的较大值，语义相等时保证返回第一个参数
  /*****************************************************************************************/
  template <class T>
  const T &max(const T &lhs, const T &rhs)
  {
    return lhs < rhs ? rhs : lhs;
  }
  template <class T, class Compare>
  const T &max(const T &lhs, const T &rhs, Compare comp)
  {
    return comp(lhs, rhs) ? rhs : lhs;
  }

  /*****************************************************************************************/
  // min
  // 取二者中的较小值，语义相等时保证返回第一个参数
  /*****************************************************************************************/
  template <class T>
  const T &min(const T &lhs, const T &rhs)
  {
    return rhs < lhs ? rhs : lhs;
  }

  // 重载版本使用函数对象 comp 代替比较操作
  template <class T, class Compare>
  const T &min(const T &lhs, const T &rhs, Compare comp)
  {
    return comp(rhs, lhs) ? rhs : lhs;
  }

} // namespace tinystl

#endif // !TINYSTL_ALGOBASE_H_