#ifndef MYTINYSTL_UNINITIALIZED_H_
#define MYTINYSTL_UNINITIALIZED_H_

#include "algobase.h"
#include "construct.h"
#include "iterator.h"
#include "type_traits.h"
#include "utils.h"

namespace tinystl
{

  /*****************************************************************************************/
  // uninitialized_copy
  // 把 [first, last) 上的内容复制到以 result 为起始处的空间，返回复制结束的位置
  /*****************************************************************************************/
  template <class InputIter, class ForwardIter>
  ForwardIter
  unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::true_type)
  {
    return tinystl::copy(first, last, result);
  }

  template <class InputIter, class ForwardIter>
  ForwardIter
  unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::false_type)
  {
    auto cur = result;
    try
    {
      for (; first != last; ++first, ++cur)
      {
        tinystl::construct(&*cur, *first);
      }
    }
    catch (...)
    {
      for (; result != cur; --cur)
        tinystl::destroy(&*cur);
    }
    return cur;
  }

  template <class InputIter, class ForwardIter>
  ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
  {
    return tinystl::unchecked_uninit_copy(first, last, result,
                                        std::is_trivially_copy_assignable<
                                            typename iterator_traits<ForwardIter>::
                                                value_type>{});
  }

  /*****************************************************************************************/
  // uninitialized_fill
  // 在 [first, last) 区间内填充元素值
  /*****************************************************************************************/
  template <class ForwardIter, class T>
  void
  unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T &value, std::true_type)
  {
    tinystl::fill(first, last, value);
  }

  template <class ForwardIter, class T>
  void
  unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T &value, std::false_type)
  {
    auto cur = first;
    try
    {
      for (; cur != last; ++cur)
      {
        tinystl::construct(&*cur, value);
      }
    }
    catch (...)
    {
      for (; first != cur; ++first)
        tinystl::destroy(&*first);
    }
  }

  template <class ForwardIter, class T>
  void uninitialized_fill(ForwardIter first, ForwardIter last, const T &value)
  {
    tinystl::unchecked_uninit_fill(first, last, value,
                                   std::is_trivially_copy_assignable<
                                       typename iterator_traits<ForwardIter>::
                                           value_type>{});
  }

} // namespace tinystl

#endif