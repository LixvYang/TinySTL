#ifndef TINYSTL_VECTOR_H_
#define TINYSTL_VECTOR_H_

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include "algobase.h"
#include "allocator.h"
#include "iterator.h"
#include "memory.h"
#include "utils.h"
#include "exceptdef.h"
using namespace std;

namespace tinystl
{
#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
#pragma message("#undefing marco min")
#undef min
#endif // min

  // 模板类
  template <class T, class Alloc = allocator<T>>
  class vector
  {
  public:
    typedef T value_type;
    typedef value_type *pointer;
    typedef value_type *iterator;
    typedef value_type &reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

  protected:
    typedef allocator<T> data_allocator;
    iterator start;
    iterator finish;
    iterator end_of_storage;

    void
    insert_aux(iterator position, const T &x);
    void deallocate()
    {
      if (start)
        data_allocator::deallocate(start, end_of_storage - start);
    }

    void fill_initialize(size_type n, const T &value)
    {
      start = allocate_and_fill(n, value);
      finish = start + n;
      end_of_storage = finish;
    }

  public:
    iterator begin() { return start; }
    iterator end() { return finish; }
    size_type size() const { return size_type(end() - begin()); }
    size_type capacity() const { return size_type(end_of_storage - begin()); }
    bool empty() const { return begin() == end(); }
    reference operator[](size_type n) { return *(begin() + n); }
    vector() : start(0), finish(0), end_of_storage(0) {}
    vector(size_type n, const T &value) { fill_initialize(n, value); }
    vector(int n, const T &value) { fill_initialize(n, value); }
    vector(long n, const T &value) { fill_initialize(n, value); }
    explicit vector(size_type n) { fill_initialize(n, T()); }
    ~vector()
    {
      destroy(start, finish);
      deallocate();
    }
    reference front() { return *begin(); }
    reference back() { return *(end() - 1); }
    void push_back(const T &x)
    {
      if (finish != end_of_storage)
      {
        construct(finish, x);
        ++finish;
      }
      else
      {
        insert_aux(end(), x);
      }
    }
    void pop_back()
    {
      --finish;
      destroy(finish);
    }
    iterator erase(iterator position)
    {
      if (position + 1 != end())
        std::copy(position + 1, finish, position);
      --finish;
      destroy(finish);
      return position;
    }
    iterator erase(iterator first, iterator last)
    {
      iterator i = copy(last, finish, first);
      destroy(i, finish);
      finish = finish - (last - first);
      return first;
    }

    void resize(size_type new_size, const T &x)
    {
      if (new_size < size())
      {
        erase(begin() + new_size, end());
      }
      else
      {

        (end(), new_size - size(), x);
      }
    }
    void resize(size_type new_size) { resize(new_size, T()); }
    void clear() { erase(begin(), end()); }
    void insert(iterator position, size_type n, const T &x);

  protected:
    iterator allocate_and_fill(size_type n, const T &x)
    {
      iterator result = data_allocator::allocate(n);
      uninitialized_fill_n(result, n, x);
      return result;
    }
<<<<<<< HEAD
=======

    // swap
    void swap(vector &rhs) noexcept;

  private:
    // helper functions
    //
    // initializer / destroy
    void
    try_init() noexcept;
    void init_space(size_type size, size_type cap);
    void fill_init(size_type n, const value_type &value);

    template <class Iter>
    void range_init(Iter first, Iter last);
    void destroy_and_recover(iterator first, iterator last, size_type n);
    // calculate the growth size
    size_type get_new_cap(size_type add_size);
    // assign
    void fill_assign(size_type n, const value_type &value);
    template <class IIter>
    void copy_assign(IIter first, IIter last, input_iterator_tag);

    template <class FIter>
    void copy_assign(FIter first, FIter last, forward_iterator_tag);

    // reallocate
    template <class... Args>
    void reallocate_emplace(iterator pos, Args &&...args);
    void reallocate_insert(iterator pos, const value_type &value);

    // insert

    iterator fill_insert(iterator pos, size_type n, const value_type &value);
    template <class IIter>
    void copy_insert(iterator pos, IIter first, IIter last);

    // shrink_to_fit
    void reinsert(size_type size);
>>>>>>> test
  };

  template <class T, class Alloc>
  void vector<T, Alloc>::insert(iterator position, size_type n, const T &x)
  {
    if (n != 0)
    {
<<<<<<< HEAD
      if (size_type(end_of_storage - finish) >= n)
      {
        T x_copy = x;
        const size_type elems_after = finish - position;
        iterator old_finish = finish;
        if (elems_after > n)
        {
          std::uninitialized_copy(finish - n, finish, finish);
          finish += n;
          std::copy_backward(position, old_finish - n, old_finish);
          fill(position, position + n, x_copy);
        }
        else
        {
          std::uninitialized_fill_n(finish, n - elems_after, x_copy);
          finish += n - elems_after;
          std::uninitialized_copy(position, old_finish, finish);
          finish += elems_after;
          fill(position, old_finish, x_copy);
        }
      }
      else
      {
        const size_type old_size = size();
        const size_type len = old_size + std::max(old_size, n);
        iterator new_start = data_allocator::allocate(len);
        iterator new_finish= new_start;
        __STL_TRY {
          
        }
      }
=======
      return this;
    }
    const size_type len = rhs.size();
    if (len > capacity())
    {
      vector tmp(rhs.begin(), rhs.end());
      swap(tmp);
    }
    else if (size() >= len)
    {
      auto i = std::copy(rhs.begin(), rhs.end(), begin());
      data_allocator::destroy(i, end_);
      end_ = begin_ + len;
    }
    else
    {
      std::copy(rhs.begin(), rhs.begin() + size(), begin_);
      std::uninitialized_copy(rhs.begin() + size(), rhs.end(), end_);
      cap_ = end_ = begin_ + len;
    }
  }

  template <class T>
  vector<T> &vector<T>::operator=(vector &&rhs) noexcept
  {
    destroy_and_recover(begin_, end_, cap_ - begin_);
    begin_ = rhs.begin_;
    end_ = rhs.end_;
    cap_ = rhs.cap_;
    rhs.begin_ = nullptr;
    rhs.end_ = nullptr;
    rhs.cap_ = nullptr;
    return *this;
  }

  // 预留空间大小，当原容量小于要求大小时，才会重新分配
  template <class T>
  void vector<T>::reserve(size_type n)
  {
    if (capacity() < n)
    {
      THROW_LENGTH_ERROR_IF(n > max_size(),
                            "n can not larger than max_size() in vector<T>::reserve(n)");
      const auto old_size = size();
      auto tmp = data_allocator::allocate(n);
      uninitialized_move(begin_, end_, tmp);
      data_allocator::deallocate(begin_, cap_ - begin_);
      begin_ = tmp;
      end_ = tmp + old_size;
      cap_ = begin_ + n;
    }
  }

  // 放弃多余的容量
  template <class T>
  void vector<T>::shrink_to_fit()
  {
    if (end_ < cap_)
    {
      reinsert(size());
    }
  }

  // 在 pos 位置就地构造元素，避免额外的复制或移动开销
  template <class T>
  template <class... Args>
  typename vector<T>::iterator
  vector<T>::emplace(const_iterator pos, Args &&...args)
  {
    MYSTL_DEBUG(pos >= begin() && pos <= end());
    iterator xpos = const_cast<iterator>(pos);
    const size_type n = xpos - begin_;
    if (end_ != cap_ && xpos == end_)
    {
      data_allocator::construct(tinystl::address_of(*end_), tinystl::forward<Args>(args)...);
      ++end_;
    }
    else if (end_ != cap_)
    {
      auto new_end = end_;
      data_allocator::construct(tinystl::address_of(*end_), *(end_ - 1));
      ++new_end;
      copy_backward(xpos, end_ - 1, end_);
      *xpos = value_type(tinystl::forward<Args>(args)...);
    }
    else
    {
      reallocate_emplace(xpos, tinystl::forward<Args>(args)...);
    }
    return begin() + n;
  }

  // 在尾部就地构造元素，避免额外的复制或移动开销
  template <class T>
  template <class... Args>
  void vector<T>::emplace_back(Args &&...args)
  {
    if (end_ < cap_)
    {
      data_allocator::construct(tinystl::address_of(*end_), tinystl::forward<Args>(args)...);
      ++end_;
    }
    else
    {
      reallocate_emplace(end_, tinystl::forward<Args>(args)...);
    }
  }

  template <class T>
  void vector<T>::push_back(const value_type &value)
  {
    if (end_ != cap_)
    {
      data_allocator::construct(tinystl::address_of(*end_), value);
      ++end_;
    }
    else
    {
      reallocate_insert(end_, value);
    }
  }

  // 弹出尾部元素
  template <class T>
  void vector<T>::pop_back()
  {
    MYSTL_DEBUG(!empty());
    data_allocator::destroy(end_ - 1);
    --end_;
  }
  // 在 pos 处插入元素
  template <class T>
  typename vector<T>::iterator
  vector<T>::insert(const_iterator pos, const value_type &value)
  {
    MYSTL_DEBUG(pos >= begin() && pos <= end());
    iterator xpos = const_cast<iterator>(pos);
    const size_type n = pos - begin_;
    if (end_ != cap_ && xpos == end_)
    {
      data_allocator::construct(tinystl::address_of(*end_), value);
      ++end_;
    }
    else if (end_ != cap_)
    {
      auto new_end = end_;
      data_allocator::construct(tinystl::address_of(*end_), *(end_ - 1));
      ++new_end;
      auto value_copy = value; // 避免元素因以下复制操作而被改变
      copy_backward(xpos, end_ - 1, end_);
      *xpos = tinystl::move(value_copy);
      end_ = new_end;
    }
    else
    {
      reallocate_insert(xpos, value);
    }
    return begin_ + n;
  }

  // 删除 pos 位置上的元素
  template <class T>
  typename vector<T>::iterator
  vector<T>::erase(const_iterator pos)
  {
    MYSTL_DEBUG(pos >= begin() && pos < end());
    iterator xpos = begin_ + (pos - begin());
    tinystl::move(xpos + 1, end_, xpos);
    data_allocator::destroy(end_ - 1);
    --end_;
    return xpos;
  }

  // 删除[first, last)上的元素
  template <class T>
  typename vector<T>::iterator
  vector<T>::erase(const_iterator first, const_iterator last)
  {
    MYSTL_DEBUG(first >= begin() && last <= end() && !(last < first));
    const auto n = first - begin();
    iterator r = begin_ + (first - begin());
    data_allocator::destroy(tinystl::move(r + (last - first), end_, r), end_);
    end_ = end_ - (last - first);
    return begin_ + n;
  }

  // 重置容器大小
  template <class T>
  void vector<T>::resize(size_type new_size, const value_type &value)
  {
    if (new_size < size())
    {
      erase(begin() + new_size, end());
    }
    else
    {
      insert(end(), new_size - size(), value);
    }
  }

  // 与另一个 vector 交换
  template <class T>
  void vector<T>::swap(vector<T> &rhs) noexcept
  {
    if (this != &rhs)
    {
      swap(begin_, rhs.begin_);
      swap(end_, rhs.end_);
      swap(cap_, rhs.cap_);
    }
  }

  /*****************************************************************************************/
  // helper function

  // try_init 函数，若分配失败则忽略，不抛出异常
  template <class T>
  void vector<T>::try_init() noexcept
  {
    try
    {
      begin_ = data_allocator::allocate(16);
      end_ = begin_;
      cap_ = begin_ + 16;
    }
    catch (...)
    {
      begin_ = nullptr;
      end_ = nullptr;
      cap_ = nullptr;
>>>>>>> test
    }
  }

  template <class T>
  void vector<T>::init_space(size_type size, size_type cap)
  {
    try
    {
      begin_ = data_allocator::allocate(cap);
      end_ = begin_ + size;
      cap_ = begin_ + cap;
    }
    catch (...)
    {
      begin_ = nullptr;
      end_ = nullptr;
      cap = nullptr;
      throw;
    }
  }

  template <class T>
  void vector<T>::fill_init(size_type n, const value_type &value)
  {
    const size_type init_size = tinystl::max(static_cast<size_type>(16), n);
    init_space(n, init_size);
    uninitialized_fill_n(begin_, n, value);
  }

  // range_init 函数
  template <class T>
  template <class Iter>
  void vector<T>::
      range_init(Iter first, Iter last)
  {
    const size_type init_size = tinystl::max(static_cast<size_type>(last - first),
                                             static_cast<size_type>(16));
    init_space(static_cast<size_type>(last - first), init_size);
    uninitialized_copy(first, last, begin_);
  }

  // destroy_and_recover 函数
  template <class T>
  void vector<T>::
      destroy_and_recover(iterator first, iterator last, size_type n)
  {
    data_allocator::destroy(first, last);
    data_allocator::deallocate(first, n);
  }

  // get_new_cap 函数
  template <class T>
  typename vector<T>::size_type
  vector<T>::
      get_new_cap(size_type add_size)
  {
    const auto old_size = capacity();
    THROW_LENGTH_ERROR_IF(old_size > max_size() - add_size,
                          "vector<T>'s size too big");
    if (old_size > max_size() - old_size / 2)
    {
      return old_size + add_size > max_size() - 16
                 ? old_size + add_size
                 : old_size + add_size + 16;
    }
    const size_type new_size = old_size == 0
                                   ? tinystl::max(add_size, static_cast<size_type>(16))
                                   : tinystl::max(old_size + old_size / 2, old_size + add_size);
    return new_size;
  }

  // fill_assign 函数
  template <class T>
  void vector<T>::
      fill_assign(size_type n, const value_type &value)
  {
    if (n > capacity())
    {
      vector tmp(n, value);
      swap(tmp);
    }
    else if (n > size())
    {
      fill(begin(), end(), value);
      end_ = uninitialized_fill_n(end_, n - size(), value);
    }
    else
    {
      erase(fill_n(begin_, n, value), end_);
    }
  }

  template <class T>
  template <class IIter>
  void vector<T>::copy_assign(IIter first, IIter last, input_iterator_tag)
  {
    auto cur = begin_;
    for (; first != last && cur != end_; ++first, ++cur)
    {
      *cur = *first;
    }
    if (first == last)
    {
      erase(first, last);
    }
    else
    {
      insert(end_, first, last);
    }
  }

  // 用 [first, last) 为容器赋值
  template <class T>
  template <class FIter>
  void vector<T>::
      copy_assign(FIter first, FIter last, forward_iterator_tag)
  {
    const size_type len = tinystl::distance(first, last);
    if (len > capacity())
    {
      vector tmp(first, last);
      swap(tmp);
    }
    else if (size() >= len)
    {
      auto new_end = copy(first, last, begin_);
      data_allocator::destroy(new_end, end_);
      end_ = new_end;
    }
    else
    {
      auto mid = first;
      tinystl::advance(mid, size());
      copy(first, mid, begin_);
      auto new_end = uninitialized_copy(mid, last, end_);
      end_ = new_end;
    }
  }

  // 重新分配空间并在 pos 处就地构造元素
  template <class T>
  template <class... Args>
  void vector<T>::
      reallocate_emplace(iterator pos, Args &&...args)
  {
    const auto new_size = get_new_cap(1);
    auto new_begin = data_allocator::allocate(new_size);
    auto new_end = new_begin;
    try
    {
      new_end = uninitialized_move(begin_, pos, new_begin);
      data_allocator::construct(tinystl::address_of(*new_end), tinystl::forward<Args>(args)...);
      ++new_end;
      new_end = uninitialized_move(pos, end_, new_end);
    }
    catch (...)
    {
      data_allocator::deallocate(new_begin, new_size);
      throw;
    }
    destroy_and_recover(begin_, end_, cap_ - begin_);
    begin_ = new_begin;
    end_ = new_end;
    cap_ = new_begin + new_size;
  }

  // 重新分配空间并在 pos 处插入元素
  template <class T>
  void vector<T>::reallocate_insert(iterator pos, const value_type &value)
  {
    const auto new_size = get_new_cap(1);
    auto new_begin = data_allocator::allocate(new_size);
    auto new_end = new_begin;
    const value_type &value_copy = value;
    try
    {
      new_end = uninitialized_move(begin_, pos, new_begin);
      data_allocator::construct(tinystl::address_of(*new_end), value_copy);
      ++new_end;
      new_end = uninitialized_move(pos, end_, new_end);
    }
    catch (...)
    {
      data_allocator::deallocate(new_begin, new_size);
      throw;
    }
    destroy_and_recover(begin_, end_, cap_ - begin_);
    begin_ = new_begin;
    end_ = new_end;
    cap_ = new_begin + new_size;
  }

  // fill_insert 函数
  template <class T>
  typename vector<T>::iterator
  vector<T>::
      fill_insert(iterator pos, size_type n, const value_type &value)
  {
    if (n == 0)
      return pos;
    const size_type xpos = pos - begin_;
    const value_type value_copy = value; // 避免被覆盖
    if (static_cast<size_type>(cap_ - end_) >= n)
    { // 如果备用空间大于等于增加的空间
      const size_type after_elems = end_ - pos;
      auto old_end = end_;
      if (after_elems > n)
      {
        uninitialized_copy(end_ - n, end_, end_);
        end_ += n;
        move_backward(pos, old_end - n, old_end);
        uninitialized_fill_n(pos, n, value_copy);
      }
      else
      {
        end_ = uninitialized_fill_n(end_, n - after_elems, value_copy);
        end_ = uninitialized_move(pos, old_end, end_);
        uninitialized_fill_n(pos, after_elems, value_copy);
      }
    }
    else
    { // 如果备用空间不足
      const auto new_size = get_new_cap(n);
      auto new_begin = data_allocator::allocate(new_size);
      auto new_end = new_begin;
      try
      {
        new_end = uninitialized_move(begin_, pos, new_begin);
        new_end = uninitialized_fill_n(new_end, n, value);
        new_end = uninitialized_move(pos, end_, new_end);
      }
      catch (...)
      {
        destroy_and_recover(new_begin, new_end, new_size);
        throw;
      }
      data_allocator::deallocate(begin_, cap_ - begin_);
      begin_ = new_begin;
      end_ = new_end;
      cap_ = begin_ + new_size;
    }
    return begin_ + xpos;
  }

  // copy_insert 函数
  template <class T>
  template <class IIter>
  void vector<T>::
      copy_insert(iterator pos, IIter first, IIter last)
  {
    if (first == last)
      return;
    const auto n = tinystl::distance(first, last);
    if ((cap_ - end_) >= n)
    { // 如果备用空间大小足够
      const auto after_elems = end_ - pos;
      auto old_end = end_;
      if (after_elems > n)
      {
        end_ = uninitialized_copy(end_ - n, end_, end_);
        move_backward(pos, old_end - n, old_end);
        uninitialized_copy(first, last, pos);
      }
      else
      {
        auto mid = first;
        tinystl::advance(mid, after_elems);
        end_ = uninitialized_copy(mid, last, end_);
        end_ = uninitialized_move(pos, old_end, end_);
        uninitialized_copy(first, mid, pos);
      }
    }
    else
    { // 备用空间不足
      const auto new_size = get_new_cap(n);
      auto new_begin = data_allocator::allocate(new_size);
      auto new_end = new_begin;
      try
      {
        new_end = uninitialized_move(begin_, pos, new_begin);
        new_end = uninitialized_copy(first, last, new_end);
        new_end = uninitialized_move(pos, end_, new_end);
      }
      catch (...)
      {
        destroy_and_recover(new_begin, new_end, new_size);
        throw;
      }
      data_allocator::deallocate(begin_, cap_ - begin_);
      begin_ = new_begin;
      end_ = new_end;
      cap_ = begin_ + new_size;
    }
  }

  // reinsert 函数
  template <class T>
  void vector<T>::reinsert(size_type size)
  {
    auto new_begin = data_allocator::allocate(size);
    try
    {
      uninitialized_move(begin_, end_, new_begin);
    }
    catch (...)
    {
      data_allocator::deallocate(new_begin, size);
      throw;
    }
    data_allocator::deallocate(begin_, cap_ - begin_);
    begin_ = new_begin;
    end_ = begin_ + size;
    cap_ = begin_ + size;
  }

  /*****************************************************************************************/
  // 重载比较操作符
  template <class T>
  bool operator==(const vector<T> &lhs, const vector<T> &rhs)
  {
    return lhs.size() == rhs.size() && equal((lhs.begin(), lhs.end(), rhs.begin()));
  }

  template <class T>
  bool operator<(const vector<T> &lhs, const vector<T> &rhs)
  {
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), lhs.end());
  }

  template <class T>
  bool operator!=(const vector<T> &lhs, const vector<T> &rhs)
  {
    return !(lhs == rhs);
  }

  template <class T>
  bool operator>(const vector<T> &lhs, const vector<T> &rhs)
  {
    return rhs < lhs;
  }

  template <class T>
  bool operator<=(const vector<T> &lhs, const vector<T> &rhs)
  {
    return !(rhs < lhs);
  }

  template <class T>
  bool operator>=(const vector<T> &lhs, const vector<T> &rhs)
  {
    return !(lhs < rhs);
  }

  template <class T>
  void swap(vector<T> &lhs, vector<T> &rhs)
  {
    lhs.swap(rhs);
  }

} // namespace tinystal

#endif // !TINYSTL_VECTOR_H_