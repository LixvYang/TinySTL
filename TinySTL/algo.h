#ifndef TINYSTL_ALGO_H_
#define TINYSTL_ALGO_H_

#include <algorithm>
#include <cstddef>
#include <ctime>

#include "algobase.h"
#include "memory.h"
#include "functional.h"
#include "utils.h"

namespace tinystl
{

  /*****************************************************************************************/
  // all_of
  // 检查[first, last)内是否全部元素都满足一元操作 unary_pred 为 true 的情况，满足则返回 true
  /*****************************************************************************************/
  template <class InputIter, class UnaryPredicate>
  bool all_of(InputIter first, InputIter last, UnaryPredicate unary_pred)
  {
    for (; first != last; ++first)
    {
      if (!unary_pred(*first))
      {
        return false;
      }
    }
    return true;
  }

  /*********************************************8
   * any_of
   * 检查[first,last)内是否存在某个元素满足一元操作 unary_pred为true的情况，满足则返回true
   */
  template <class InputIter, class UnaryPredicate>
  bool any_of(InputIter first, InputIter last, UnaryPredicate unary_pred)
  {
    while (first != last)
    {
      if (unary_pred(*first))
        return true;
      ++first;
    }
    return false;
  }

  /*****************************************************************************************/
  // none_of
  // 检查[first, last)内是否全部元素都不满足一元操作 unary_pred 为 true 的情况，满足则返回 true
  /*****************************************************************************************/
  template <class InputIter, class UnaryPredicate>
  bool none_of(InputIter first, InputIter last, UnaryPredicate unary_pred)
  {
    for (; first != last; ++first)
    {
      if (unary_pred(*first))
        return false;
    }
    return true;
  }

  /*****************************************************************************************/
  // count
  // 对[first, last)区间内的元素与给定值进行比较，缺省使用 operator==，返回元素相等的个数
  /*****************************************************************************************/
  template <class InputIter, class T>
  size_t count(InputIter first, InputIter last, const T &value)
  {
    size_t n = 0;
    for (; first != last; ++first)
    {
      if (*first == value)
        ++n;
    }
    return n;
  }

  /*****************************************************************************************/
  // count_if
  // 对[first, last)区间内的每个元素都进行一元 unary_pred 操作，返回结果为 true 的个数
  /*****************************************************************************************/
  template <class InputIter, class UnaryPredicate>
  size_t count_if(InputIter first, InputIter last, UnaryPredicate unary_pred)
  {
    size_t n = 0;
    for (; first != last; ++first)
    {
      if (unary_pred(*first))
      {
        ++n;
      }
    }
    return n;
  }

  /*****************************************************************************************/
  // find
  // 在[first, last)区间内找到等于 value 的元素，返回指向该元素的迭代器
  /*****************************************************************************************/
  template <class InputIter, class T>
  InputIter find(InputIter first, InputIter last, const T &value)
  {
    while (first != last && *first != value)
    {
      ++first;
    }
    return first;
  }

  /*****************************************************************************************/
  // find_if
  // 在[first, last)区间内找到第一个令一元操作 unary_pred 为 true 的元素并返回指向该元素的迭代器
  /*****************************************************************************************/
  template <class InputIter, class UnaryPredicate>
  InputIter
  find_if(InputIter first, InputIter last, UnaryPredicate unary_pred)
  {
    while (first != last && !unary_pred(*first))
      ++first;
    return first;
  }

  /*****************************************************************************************/
  // find_if_not
  // 在[first, last)区间内找到第一个令一元操作 unary_pred 为 false 的元素并返回指向该元素的迭代器
  /*****************************************************************************************/
  template <class InputIter, class UnaryPredicate>
  InputIter
  find_if_not(InputIter first, InputIter last, UnaryPredicate unary_pred)
  {
    while (first != last && unary_pred(*first))
      ++first;
    return first;
  }

  template <class ForwardIter1, class ForwardIter2>
  ForwardIter1
  search(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2)
  {
    auto d1 = tinystl::distance(first1, last1);
    auto d2 = tinystl::distance(first2, last2);
    if (d1 < d2)
      return last1;
    auto current1 = first1;
    auto current2 = first2;
    while (current2 != last2)
    {
      if (*current1 == *current2)
      {
        ++current1;
        ++current2;
      }
      else
      {
        if (d1 == d2)
        {
          return last1;
        }
        else
        {
          current1 = ++first1;
          current2 = first2;
          --d1;
        }
      }
    }
    return first1;
  }

  // 重载版本使用函数对象 comp 代替比较操作
  template <class ForwardIter1, class ForwardIter2, class Compared>
  ForwardIter1
  search(ForwardIter1 first1, ForwardIter1 last1,
         ForwardIter2 first2, ForwardIter2 last2, Compared comp)
  {
    auto d1 = tinystl::distance(first1, last1);
    auto d2 = tinystl::distance(first2, last2);
    if (d1 < d2)
      return last1;
    auto current1 = first1;
    auto current2 = first2;
    while (current2 != last2)
    {
      if (comp(*current1, *current2))
      {
        ++current1;
        ++current2;
      }
      else
      {
        if (d1 == d2)
        {
          return last1;
        }
        else
        {
          current1 = ++first1;
          current2 = first2;
          --d1;
        }
      }
    }
    return first1;
  }

  /*****************************************************************************************/
  // search_n
  // 在[first, last)中查找连续 n 个 value 所形成的子序列，返回一个迭代器指向该子序列的起始处
  /*****************************************************************************************/
  template <class ForwardIter, class Size, class T>
  ForwardIter search_n(ForwardIter first, ForwardIter last, Size n, const T &value)
  {
    if (n <= 0)
    {
      return first;
    }
    else
    {
      first = tinystl::find(first, last, value);
      while (first != last)
      {
        auto m = n - 1;
        auto i = first;
        ++i;
        while (i != last && m != 0 && *i == value)
        {
          ++i;
          --m;
        }
        if (m == 0)
        {
          return first;
        }
        else
        {
          first = tinystl::find(i, last, value);
        }
      }
      return last;
    }
  }

  // 重载版本使用函数对象 comp 代替比较操作
  template <class ForwardIter, class Size, class T, class Compared>
  ForwardIter
  search_n(ForwardIter first, ForwardIter last,
           Size n, const T &value, Compared comp)
  {
    if (n <= 0)
    {
      return first;
    }
    else
    {
      while (first != last)
      {
        if (comp(*first, value))
          break;
        ++first;
      }
      while (first != last)
      {
        auto m = n - 1;
        auto i = first;
        ++i;
        while (i != last && m != 0 && comp(*i, value))
        {
          ++i;
          --m;
        }
        if (m == 0)
        {
          return first;
        }
        else
        {
          while (i != last)
          {
            if (comp(*i, value))
              break;
            ++i;
          }
          first = i;
        }
      }
      return last;
    }
  }

  /*****************************************************************************************/
  // find_end
  // 在[first1, last1)区间中查找[first2, last2)最后一次出现的地方，若不存在返回 last1
  /*****************************************************************************************/
  // find_end_dispatch 的 forward_iterator_tag 版本
  template <class ForwardIter1, class ForwardIter2>
  ForwardIter1
  find_end_disatch(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2, forward_iterator_tag, forward_iterator_tag)
  {
    if (first2 == last1)
    {
      return last1;
    }
    else
    {
      auto result = last1;
      while (true)
      {
        // 利用 search 查找某个子序列的首次出现点，找不到则返回 last1
        auto new_result = tinystl::search(first1, last1, first2, last2);
        if (new_result == last1)
        {
          return result;
        }
        else
        {
          result = new_result;
          first1 = new_result;
          ++first1;
        }
      }
    }
  }

  // find_end_dispatch 的 bidirectional_iterator_tag 版本
  template <class BidirectionalIter1, class BidirectionalIter2>
  BidirectionalIter1
  find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1,
                    BidirectionalIter2 first2, BidirectionalIter2 last2,
                    bidirectional_iterator_tag, bidirectional_iterator_tag)
  {
    typedef reverse_iterator<BidirectionalIter1> reviter1;
    typedef reverse_iterator<BidirectionalIter2> reviter2;
    reviter1 rlast1(first1);
    reviter2 rlast2(first2);
    reviter1 rresult = tinystl::search(reviter1(last1), rlast1, reviter2(last2), rlast2);
    if (rresult == rlast1)
    {
      return last1;
    }
    else
    {
      auto result = rresult.base();
      tinystl::advance(result, -tinystl::distance(first2, last2));
      return result;
    }
  }

  template <class ForwardIter1, class ForwardIter2>
  ForwardIter1
  find_end(ForwardIter1 first1, ForwardIter1 last1,
           ForwardIter2 first2, ForwardIter2 last2)
  {
    typedef typename iterator_traits<ForwardIter1>::iterator_category Category1;
    typedef typename iterator_traits<ForwardIter2>::iterator_category Category2;
    return tinystl::find_end_dispatch(first1, last1, first2, last2, Category1(), Category2());
  }

  // 重载版本使用函数对象 comp 代替比较操作
  // find_end_dispatch 的 forward_iterator_tag 版本
  template <class ForwardIter1, class ForwardIter2, class Compared>
  ForwardIter1
  find_end_dispatch(ForwardIter1 first1, ForwardIter1 last1,
                    ForwardIter2 first2, ForwardIter2 last2,
                    forward_iterator_tag, forward_iterator_tag, Compared comp)
  {
    if (first2 == last2)
    {
      return last1;
    }
    else
    {
      auto result = last1;
      while (true)
      {
        // 利用 search 查找某个子序列的首次出现点，找不到则返回 last1
        auto new_result = tinystl::search(first1, last1, first2, last2, comp);
        if (new_result == last1)
        {
          return result;
        }
        else
        {
          result = new_result;
          first1 = new_result;
          ++first1;
        }
      }
    }
  }

  // find_end_dispatch 的 bidirectional_iterator_tag 版本
  template <class BidirectionalIter1, class BidirectionalIter2, class Compared>
  BidirectionalIter1
  find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1,
                    BidirectionalIter2 first2, BidirectionalIter2 last2,
                    bidirectional_iterator_tag, bidirectional_iterator_tag, Compared comp)
  {
    typedef reverse_iterator<BidirectionalIter1> reviter1;
    typedef reverse_iterator<BidirectionalIter2> reviter2;
    reviter1 rlast1(first1);
    reviter2 rlast2(first2);
    reviter1 rresult = tinystl::search(reviter1(last1), rlast1, reviter2(last2), rlast2, comp);
    if (rresult == rlast1)
    {
      return last1;
    }
    else
    {
      auto result = rresult.base();
      tinystl::advance(result, -tinystl::distance(first2, last2));
      return result;
    }
  }

  template <class ForwardIter1, class ForwardIter2, class Compared>
  ForwardIter1
  find_end(ForwardIter1 first1, ForwardIter1 last1,
           ForwardIter2 first2, ForwardIter2 last2, Compared comp)
  {
    typedef typename iterator_traits<ForwardIter1>::iterator_category Category1;
    typedef typename iterator_traits<ForwardIter2>::iterator_category Category2;
    return tinystl::find_end_dispatch(first1, last1, first2, last2, Category1(), Category2(), comp);
  }

  /*****************************************************************************************/
  // find_first_of
  // 在[first1, last1)中查找[first2, last2)中的某些元素，返回指向第一次出现的元素的迭代器
  /*****************************************************************************************/
  template <class InputIter, class ForwardIter>
  InputIter
  find_first_of(InputIter first1, InputIter last1, ForwardIter first2, ForwardIter last2)
  {
    for (; first1 != last1; ++first1)
    {
      for (auto iter = first2; iter != last2; ++iter)
      {
        if (*first1 == *iter)
        {
          return first1;
        }
      }
    }
    return last1;
  }

  // 重载版本使用函数对象 comp 代替比较操作
  template <class InputIter, class ForwardIter, class Compared>
  InputIter
  find_first_of(InputIter first1, InputIter last1,
                ForwardIter first2, ForwardIter last2, Compared comp)
  {
    for (; first1 != last1; ++first1)
    {
      for (auto iter = first2; iter != last2; ++iter)
      {
        if (comp(*first1, *iter))
          return first1;
      }
    }
    return last1;
  }

  /*****************************************************************************************/
  // for_each
  // 使用一个函数对象 f 对[first, last)区间内的每个元素执行一个 operator() 操作，但不能改变元素内容
  // f() 可返回一个值，但该值会被忽略
  /*****************************************************************************************/
  template <class InputIter, class Function>
  Function for_each(InputIter first, InputIter last, Function f)
  {
    while (first != last)
    {
      f(*first);
      ++first;
    }
    return f;
  }

  /*****************************************************************************************/
  // adjacent_find
  // 找出第一对匹配的相邻元素，缺省使用 operator== 比较，如果找到返回一个迭代器，指向这对元素的第一个元素
  /*****************************************************************************************/
  template <class ForwardIter>
  ForwardIter adjacent_find(ForwardIter first, ForwardIter last)
  {
    if (first == last)
    {
      return last;
    }
    auto next = first;
    while (++next != last)
    {
      if (*first == *next)
      {
        return first;
      }
      first = next;
    }
    return last;
  }

  // 重载版本使用函数对象 comp 代替比较操作
  template <class ForwardIter, class Compared>
  ForwardIter adjacent_find(ForwardIter first, ForwardIter last, Compared comp)
  {
    if (first == last)
      return last;
    auto next = first;
    while (++next != last)
    {
      if (comp(*first, *next))
        return first;
      first = next;
    }
    return last;
  }

  /*****************************************************************************************/
  // lower_bound
  // 在[first, last)中查找第一个不小于 value 的元素，并返回指向它的迭代器，若没有则返回 last
  /*****************************************************************************************/
  // lbound_dispatch 的 forward_iterator_tag 版本
  template <class ForwardIter, class T>
  ForwardIter
  lbound_dispatch(ForwardIter first, ForwardIter last, const T &value, forward_iterator_tag)
  {
    auto len = tinystl::distance(first, last);
    auto half = len;
    ForwardIter middle;
    while (len >> 1)
    {
      half = len >> 1;
      middle = first;
      tinystl::advance(middle, half);
      if (*middle < value)
      {
        first = middle;
        ++first;
        len = len - half - 1;
      }
      else
      {
        len = half;
      }
    }
    return first;
  }

  // lbound_dispatch 的 random_access_iterator_tag 版本
  template <class RandomIter, class T>
  RandomIter
  lbound_dispatch(RandomIter first, RandomIter last,
                  const T &value, random_access_iterator_tag)
  {
    auto len = last - first;
    auto half = len;
    RandomIter middle;
    while (len > 0)
    {
      half = len >> 1;
      middle = first + half;
      if (*middle < value)
      {
        first = middle + 1;
        len = len - half - 1;
      }
      else
      {
        len = half;
      }
    }
    return first;
  }

  template <class ForwardIter, class T>
  ForwardIter
  lower_bound(ForwardIter first, ForwardIter last, const T &value)
  {
    return tinystl::lbound_dispatch(first, last, value, iterator_category(first));
  }

  // 重载版本使用函数对象 comp 代替比较操作
  // lbound_dispatch 的 forward_iterator_tag 版本
  template <class ForwardIter, class T, class Compared>
  ForwardIter
  lbound_dispatch(ForwardIter first, ForwardIter last,
                  const T &value, forward_iterator_tag, Compared comp)
  {
    auto len = tinystl::distance(first, last);
    auto half = len;
    ForwardIter middle;
    while (len > 0)
    {
      half = len >> 1;
      middle = first;
      tinystl::advance(middle, half);
      if (comp(*middle, value))
      {
        first = middle;
        ++first;
        len = len - half - 1;
      }
      else
      {
        len = half;
      }
    }
    return first;
  }

  // lbound_dispatch 的 random_access_iterator_tag 版本
  template <class RandomIter, class T, class Compared>
  RandomIter
  lbound_dispatch(RandomIter first, RandomIter last,
                  const T &value, random_access_iterator_tag, Compared comp)
  {
    auto len = last - first;
    auto half = len;
    RandomIter middle;
    while (len > 0)
    {
      half = len >> 1;
      middle = first + half;
      if (comp(*middle, value))
      {
        first = middle + 1;
        len = len - half - 1;
      }
      else
      {
        len = half;
      }
    }
    return first;
  }

  template <class ForwardIter, class T, class Compared>
  ForwardIter
  lower_bound(ForwardIter first, ForwardIter last, const T &value, Compared comp)
  {
    return tinystl::lbound_dispatch(first, last, value, iterator_category(first), comp);
  }

  /*****************************************************************************************/
  // upper_bound
  // 在[first, last)中查找第一个大于value 的元素，并返回指向它的迭代器，若没有则返回 last
  /*****************************************************************************************/
  // ubound_dispatch 的 forward_iterator_tag 版本
  template <class ForwardIter, class T>
  ForwardIter
  ubound_dispatch(ForwardIter first, ForwardIter last, const T &value, forward_iterator_tag)
  {
    auto len = tinystl::distance(first, last);
    auto half = len;
    ForwardIter middle;
    while (len > 0)
    {
      half = len >> 1;
      middle = first;
      tinystl::advance(middle, half);
      if (value < *middle)
      {
        len = half;
      }
      else
      {
        first = middle;
        ++first;
        len = len - half - 1;
      }
    }
    return first;
  }

  // ubound_dispatch 的 random_access_iterator_tag 版本
  template <class RandomIter, class T>
  RandomIter
  ubound_dispatch(RandomIter first, RandomIter last,
                  const T &value, random_access_iterator_tag)
  {
    auto len = last - first;
    auto half = len;
    RandomIter middle;
    while (len > 0)
    {
      half = len >> 1;
      middle = first + half;
      if (value < *middle)
      {
        len = half;
      }
      else
      {
        first = middle + 1;
        len = len - half - 1;
      }
    }
    return first;
  }

  template <class ForwardIter, class T>
  ForwardIter
  upper_bound(ForwardIter first, ForwardIter last, const T &value)
  {
    return tinystl::ubound_dispatch(first, last, value, iterator_category(first));
  }

  // 重载版本使用函数对象 comp 代替比较操作
  // ubound_dispatch 的 forward_iterator_tag 版本
  template <class ForwardIter, class T, class Compared>
  ForwardIter
  ubound_dispatch(ForwardIter first, ForwardIter last,
                  const T &value, forward_iterator_tag, Compared comp)
  {
    auto len = tinystl::distance(first, last);
    auto half = len;
    ForwardIter middle;
    while (len > 0)
    {
      half = len >> 1;
      middle = first;
      tinystl::advance(middle, half);
      if (comp(value, *middle))
      {
        len = half;
      }
      else
      {
        first = middle;
        ++first;
        len = len - half - 1;
      }
    }
    return first;
  }

  // ubound_dispatch 的 random_access_iterator_tag 版本
  template <class RandomIter, class T, class Compared>
  RandomIter
  ubound_dispatch(RandomIter first, RandomIter last,
                  const T &value, random_access_iterator_tag, Compared comp)
  {
    auto len = last - first;
    auto half = len;
    RandomIter middle;
    while (len > 0)
    {
      half = len >> 1;
      middle = first + half;
      if (comp(value, *middle))
      {
        len = half;
      }
      else
      {
        first = middle + 1;
        len = len - half - 1;
      }
    }
    return first;
  }

  template <class ForwardIter, class T, class Compared>
  ForwardIter
  upper_bound(ForwardIter first, ForwardIter last, const T &value, Compared comp)
  {
    return tinystl::ubound_dispatch(first, last, value, iterator_category(first), comp);
  }

  /*****************************************************************************************/
  // binary_search
  // 二分查找，如果在[first, last)内有等同于 value 的元素，返回 true，否则返回 false
  /*****************************************************************************************/
  template <class ForwardIter, class T>
  bool binary_search(ForwardIter first, ForwardIter last, const T &value)
  {
    auto i = tinystl::lower_bound(first, last, value);
    return i != last && !(value < *i);
  }

  // 重载版本使用函数对象 comp 代替比较操作
  template <class ForwardIter, class T, class Compared>
  bool binary_search(ForwardIter first, ForwardIter last, const T &value, Compared comp)
  {
    auto i = tinystl::lower_bound(first, last, value);
    return i != last && !comp(value, *i);
  }

  /*****************************************************************************************/
  // equal_range
  // 查找[first,last)区间中与 value 相等的元素所形成的区间，返回一对迭代器指向区间首尾
  // 第一个迭代器指向第一个不小于 value 的元素，第二个迭代器指向第一个大于 value 的元素
  /*****************************************************************************************/
  // erange_dispatch 的 forward_iterator_tag 版本
  template <class ForwardIter, class T>
  tinystl::pair<ForwardIter, ForwardIter>
  equal_range(ForwardIter first, ForwardIter last, const T &value, forward_iterator_tag)
  {
    auto len = tinystl::distance(first, last);
    auto half = len;
    ForwardIter middle, left, right;
    while (len > 0)
    {
      half = len >> 1;
      middle = first;
      tinystl::advance(middle, half);
      if (*middle < value)
      {
        first = middle;
        ++first;
        len = len - half - 1;
      }
      else if (value < *middle)
      {
        len = half;
      }
      else
      {
        left = tinystl::lower_bound(first, last, value);
        tinystl::advance(first, len);
        right = tinystl::upper_bound(++middle, first, value);
        return tinystl::pair<ForwardIter, ForwardIter>(left, right);
      }
    }
    return tinystl::pair<ForwardIter, ForwardIter>(last, last);
  }

  // erange_dispatch 的 random_access_iterator_tag 版本
  template <class RandomIter, class T>
  tinystl::pair<RandomIter, RandomIter>
  erange_dispatch(RandomIter first, RandomIter last,
                  const T &value, random_access_iterator_tag)
  {
    auto len = last - first;
    auto half = len;
    RandomIter middle, left, right;
    while (len > 0)
    {
      half = len >> 1;
      middle = first + half;
      if (*middle < value)
      {
        first = middle + 1;
        len = len - half - 1;
      }
      else if (value < *middle)
      {
        len = half;
      }
      else
      {
        left = tinystl::lower_bound(first, middle, value);
        right = tinystl::upper_bound(++middle, first + len, value);
        return tinystl::pair<RandomIter, RandomIter>(left, right);
      }
    }
    return tinystl::pair<RandomIter, RandomIter>(last, last);
  }

  template <class ForwardIter, class T>
  tinystl::pair<ForwardIter, ForwardIter>
  equal_range(ForwardIter first, ForwardIter last, const T &value)
  {
    return tinystl::erange_dispatch(first, last, value, iterator_category(first));
  }

  // 重载版本使用函数对象 comp 代替比较操作
  // erange_dispatch 的 forward iterator 版本
  template <class ForwardIter, class T, class Compared>
  tinystl::pair<ForwardIter, ForwardIter>
  erange_dispatch(ForwardIter first, ForwardIter last,
                  const T &value, forward_iterator_tag, Compared comp)
  {
    auto len = tinystl::distance(first, last);
    auto half = len;
    ForwardIter middle, left, right;
    while (len > 0)
    {
      half = len >> 1;
      middle = first;
      tinystl::advance(middle, half);
      if (comp(*middle, value))
      {
        first = middle;
        ++first;
        len = len - half - 1;
      }
      else if (comp(value, *middle))
      {
        len = half;
      }
      else
      {
        left = tinystl::lower_bound(first, last, value, comp);
        tinystl::advance(first, len);
        right = tinystl::upper_bound(++middle, first, value, comp);
        return tinystl::pair<ForwardIter, ForwardIter>(left, right);
      }
    }
    return tinystl::pair<ForwardIter, ForwardIter>(last, last);
  }

  // erange_dispatch 的 random access iterator 版本
  template <class RandomIter, class T, class Compared>
  tinystl::pair<RandomIter, RandomIter>
  erange_dispatch(RandomIter first, RandomIter last,
                  const T &value, random_access_iterator_tag, Compared comp)
  {
    auto len = last - first;
    auto half = len;
    RandomIter middle, left, right;
    while (len > 0)
    {
      half = len >> 1;
      middle = first + half;
      if (comp(*middle, value))
      {
        first = middle + 1;
        len = len - half - 1;
      }
      else if (comp(value, *middle))
      {
        len = half;
      }
      else
      {
        left = tinystl::lower_bound(first, middle, value, comp);
        right = tinystl::upper_bound(++middle, first + len, value, comp);
        return tinystl::pair<RandomIter, RandomIter>(left, right);
      }
    }
    return tinystl::pair<RandomIter, RandomIter>(last, last);
  }

  template <class ForwardIter, class T, class Compared>
  tinystl::pair<ForwardIter, ForwardIter>
  equal_range(ForwardIter first, ForwardIter last, const T &value, Compared comp)
  {
    return tinystl::erange_dispatch(first, last, value, iterator_category(first), comp);
  }

  /*****************************************************************************************/
  // generate
  // 将函数对象 gen 的运算结果对[first, last)内的每个元素赋值
  /*****************************************************************************************/
  template <class ForwardIter, class Generator>
  void generate(ForwardIter first, ForwardIter last, Generator gen)
  {
    for (; first != last; ++first)
    {
      *first = gen();
    }
  }

  /*****************************************************************************************/
  // generate_n
  // 用函数对象 gen 连续对 n 个元素赋值
  /*****************************************************************************************/
  template <class ForwardIter, class Size, class Generator>
  void generate_n(ForwardIter first, Size n, Generator gen)
  {
    for (; n > 0; --n, ++first)
    {
      *first = gen();
    }
  }

  /*****************************************************************************************/
  // includes
  // 判断序列一S1 是否包含序列二S2
  /*****************************************************************************************/
  template <class InputIter1, class InputIter2>
  bool includes(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2)
  {
    while (first1 != last1 && first2 != last2)
    {
      if (*first2 < *first1)
      {
        return false;
      }
      else if (*first1 < *first2)
      {
        ++first1;
      }
      else
      {
        ++first1, ++first2;
      }
    }
    return first2 == last2;
  }

  // 重载版本使用函数对象 comp 代替比较操作
  template <class InputIter1, class InputIter2, class Compared>
  bool includes(InputIter1 first1, InputIter1 last1,
                InputIter2 first2, InputIter2 last2, Compared comp)
  {
    while (first1 != last1 && first2 != last2)
    {
      if (comp(*first2, *first1))
      {
        return false;
      }
      else if (comp(*first1, *first2))
      {
        ++first1;
      }
      else
      {
        ++first1, ++first2;
      }
    }
    return first2 == last2;
  }

  /*****************************************************************************************/
  // is_heap
  // 检查[first, last)内的元素是否为一个堆，如果是，则返回 true
  /*****************************************************************************************/
  template <class RandomIter>
  bool is_heap(RandomIter first, RandomIter last)
  {
    auto n = tinystl::distance(first, last);
    auto parent = 0;
    for (auto child = 1; child < n; ++child)
    {
      if (first[parent] < first[child])
        return false;
      if ((child & 1) == 0)
        ++parent;
    }
    return true;
  }

  // 重载版本使用函数对象 comp 代替比较操作
  template <class RandomIter, class Compared>
  bool is_heap(RandomIter first, RandomIter last, Compared comp)
  {
    auto n = tinystl::distance(first, last);
    auto parent = 0;
    for (auto child = 1; child < n; ++child)
    {
      if (comp(first[parent], first[child]))
        return false;
      if ((child & 1) == 0)
        ++parent;
    }
    return true;
  }

  /*****************************************************************************************/
  // is_sorted
  // 检查[first, last)内的元素是否升序，如果是升序，则返回 true
  /*****************************************************************************************/
  template <class ForwardIter>
  bool is_sorted(ForwardIter first, ForwardIter last)
  {
    if (first == last)
      return true;
    auto next = first;
    ++next;
    for (; next != last; first = next, ++next)
    {
      if (*next < *first)
        return false;
    }
    return true;
  }

  // 重载版本使用函数对象 comp 代替比较操作
  template <class ForwardIter, class Compared>
  bool is_sorted(ForwardIter first, ForwardIter last, Compared comp)
  {
    if (first == last)
      return true;
    auto next = first;
    ++next;
    for (; next != last; first = next, ++next)
    {
      if (comp(*next, *first))
        return false;
    }
    return true;
  }

  /*****************************************************************************************/
  // median
  // 找出三个值的中间值
  /*****************************************************************************************/
  template <class T>
  const T &median(const T &left, const T &mid, const T &right)
  {
    if (left < mid)
      if (mid < right) // left < mid < right
        return mid;
      else if (left < right) // left < right <= mid
        return right;
      else // right <= left < mid
        return left;
    else if (left < right) // mid <= left < right
      return left;
    else if (mid < right) // mid < right <= left
      return right;
    else // right <= mid <= left
      return mid;
  }

  // 重载版本使用函数对象 comp 代替比较操作
  template <class T, class Compared>
  const T &median(const T &left, const T &mid, const T &right, Compared comp)
  {
    if (comp(left, mid))
      if (comp(mid, right))
        return mid;
      else if (comp(left, right))
        return right;
      else
        return left;
    else if (comp(left, right))
      return left;
    else if (comp(mid, right))
      return right;
    else
      return mid;
  }

  /*****************************************************************************************/
  // max_element
  // 返回一个迭代器，指向序列中最大的元素
  /*****************************************************************************************/
  template <class ForwardIter>
  ForwardIter max_element(ForwardIter first, ForwardIter last)
  {
    if (first == last)
      return first;
    auto result = first;
    while (++first != last)
    {
      if (*result < last)
      {
        result = first;
      }
    }
    return result;
  }

  // 重载版本使用函数对象 comp 代替比较操作
  template <class ForwardIter, class Compared>
  ForwardIter max_element(ForwardIter first, ForwardIter last, Compared comp)
  {
    if (first == last)
      return first;
    auto result = first;
    while (++first != last)
    {
      if (comp(*result, *first))
        result = first;
    }
    return result;
  }

  /*****************************************************************************************/
  // min_element
  // 返回一个迭代器，指向序列中最小的元素
  /*****************************************************************************************/
  template <class ForwardIter>
  ForwardIter min_elememt(ForwardIter first, ForwardIter last)
  {
    if (first == last)
      return first;
    auto result = first;
    while (++first != last)
    {
      if (*first < *result)
        result = first;
    }
    return result;
  }

  // 重载版本使用函数对象 comp 代替比较操作
  template <class ForwardIter, class Compared>
  ForwardIter min_elememt(ForwardIter first, ForwardIter last, Compared comp)
  {
    if (first == last)
      return first;
    auto result = first;
    while (++first != last)
    {
      if (comp(*first, *result))
        result = first;
    }
    return result;
  }

  /*****************************************************************************************/
  // swap_ranges
  // 将[first1, last1)从 first2 开始，交换相同个数元素
  // 交换的区间长度必须相同，两个序列不能互相重叠，返回一个迭代器指向序列二最后一个被交换元素的下一位置
  /*****************************************************************************************/
  template <class ForwardIter1, class ForwardIter2>
  ForwardIter2
  swap_ranges(ForwardIter1 first1, ForwardIter1 last1,
              ForwardIter2 first2)
  {
    for (; first1 != last1; ++first1, ++first2)
    {
      tinystl::iter_swap(first1, first2);
    }
    return first2;
  }

  /*****************************************************************************************/
  // transform
  // 第一个版本以函数对象 unary_op 作用于[first, last)中的每个元素并将结果保存至 result 中
  // 第二个版本以函数对象 binary_op 作用于两个序列[first1, last1)、[first2, last2)的相同位置
  /*****************************************************************************************/
  template <class InputIter, class OutputIter, class UnaryOperation>
  OutputIter
  transform(InputIter first, InputIter last,
            OutputIter result, UnaryOperation unary_op)
  {
    for (; first != last; ++first, ++result)
    {
      *result = unary_op(*first);
    }
    return result;
  }

  template <class InputIter1, class InputIter2, class OutputIter, class BinaryOperation>
  OutputIter
  transform(InputIter1 first1, InputIter1 last1,
            InputIter2 first2, OutputIter result, BinaryOperation binary_op)
  {
    for (; first1 != last1; ++first1, ++first2, ++result)
    {
      *result = binary_op(*first1, *first2);
    }
    return result;
  }

  /*****************************************************************************************/
  // remove_copy
  // 移除区间内与指定 value 相等的元素，并将结果复制到以 result 标示起始位置的容器上
  /*****************************************************************************************/
  template <class InputIter, class OutputIter, class T>
  OutputIter
  remove_copy(InputIter first, InputIter last, OutputIter result, const T &value)
  {
    for (; first != last; ++first)
    {
      if (*first != value)
      {
        *result++ = *first;
      }
    }
    return first;
  }

  /*****************************************************************************************/
  // remove
  // 移除所有与指定 value 相等的元素
  // 并不从容器中删除这些元素，所以 remove 和 remove_if 不适用于 array
  /*****************************************************************************************/
  template <class ForwardIter, class T>
  ForwardIter remove(ForwardIter first, ForwardIter last, const T &value)
  {
    first = tinystl::find(first, last, value); // 利用 find 找出第一个匹配的地方
    auto next = first;
    return first == last ? first : tinystl::remove_copy(++next, last, first, value);
  }

  /*****************************************************************************************/
  // remove_copy_if
  // 移除区间内所有令一元操作 unary_pred 为 true 的元素，并将结果复制到以 result 为起始位置的容器上
  /*****************************************************************************************/
  template <class InputIter, class OutputIter, class UnaryPredicate>
  OutputIter
  remove_copy_if(InputIter first, InputIter last,
                 OutputIter result, UnaryPredicate unary_pred)
  {
    for (; first != last; ++first)
    {
      if (!unary_pred(*first))
      {
        *result = *first;
        ++result;
      }
    }
    return result;
  }

  /*****************************************************************************************/
  // remove_if
  // 移除区间内所有令一元操作 unary_pred 为 true 的元素
  /*****************************************************************************************/
  template <class ForwardIter, class UnaryPredicate>
  ForwardIter
  remove_if(ForwardIter first, ForwardIter last, UnaryPredicate unary_pred)
  {
    first = tinystl::find_if(first, last, unary_pred); // 利用 find_if 找出第一个匹配的地方
    auto next = first;
    return first == last ? first : tinystl::remove_copy_if(++next, last, first, unary_pred);
  }

  /*****************************************************************************************/
  // replace
  // 将区间内所有的 old_value 都以 new_value 替代
  /*****************************************************************************************/
  template <class ForwardIter, class T>
  void replace(ForwardIter first, ForwardIter last,
               const T &old_value, const T &new_value)
  {
    for (; first != last; ++first)
    {
      if (*first == old_value)
        *first = new_value;
    }
  }

  /*****************************************************************************************/
  // replace_copy
  // 行为与 replace 类似，不同的是将结果复制到 result 所指的容器中，原序列没有改变
  /*****************************************************************************************/
  template <class InputIter, class OutputIter, class T>
  OutputIter
  replace_copy(InputIter first, InputIter last,
               OutputIter result, const T &old_value, const T &new_value)
  {
    for (; first != last; ++first, ++result)
    {
      *result = *first == old_value ? new_value : *first;
    }
    return result;
  }

  /*****************************************************************************************/
  // replace_copy_if
  // 行为与 replace_if 类似，不同的是将结果复制到 result 所指的容器中，原序列没有改变
  /*****************************************************************************************/
  template <class InputIter, class OutputIter, class UnaryPredicate, class T>
  OutputIter
  replace_copy_if(InputIter first, InputIter last,
                  OutputIter result, UnaryPredicate unary_pred, const T &new_value)
  {
    for (; first != last; ++first, ++result)
    {
      *result = unary_pred(*first) ? new_value : *first;
    }
    return result;
  }

  /*****************************************************************************************/
  // replace_if
  // 将区间内所有令一元操作 unary_pred 为 true 的元素都用 new_value 替代
  /*****************************************************************************************/
  template <class ForwardIter, class UnaryPredicate, class T>
  void replace_if(ForwardIter first, ForwardIter last,
                  UnaryPredicate unary_pred, const T &new_value)
  {
    for (; first != last; ++first)
    {
      if (unary_pred(*first))
        *first = new_value;
    }
  }

  /*****************************************************************************************/
  // reverse
  // 将[first, last)区间内的元素反转
  /*****************************************************************************************/
  // reverse_dispatch 的 bidirectional_iterator_tag 版本
  template <class BidirectionalIter>
  void reverse_dispatch(BidirectionalIter first, BidirectionalIter last,
                        bidirectional_iterator_tag)
  {
    while (true)
    {
      if (first == last || first == --last)
        return;
      tinystl::iter_swap(first++, last);
    }
  }

  // reverse_dispatch 的 random_access_iterator_tag 版本
  template <class RandomIter>
  void reverse_dispatch(RandomIter first, RandomIter last,
                        random_access_iterator_tag)
  {
    while (first < last)
      tinystl::iter_swap(first++, --last);
  }

  template <class BidirectionalIter>
  void reverse(BidirectionalIter first, BidirectionalIter last)
  {
    tinystl::reverse_dispatch(first, last, iterator_category(first));
  }
  /*****************************************************************************************/
  // reverse_copy
  // 行为与 reverse 类似，不同的是将结果复制到 result 所指容器中
  /*****************************************************************************************/
  template <class BidirectionalIter, class OutputIter>
  OutputIter
  reverse_copy(BidirectionalIter first, BidirectionalIter last,
               OutputIter result)
  {
    while (first != last)
    {
      --last;
      *result = *last;
      ++result;
    }
    return result;
  }

  

} // namespace tinystl

#endif // !TINYSTL_ALGO_H_