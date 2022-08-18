#ifndef TINYSTL_VECTOR_H_
#define TINYSTL_VECTOR_H_

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include "allocator.h"
#include "iterator.h"
#include "utils.h"
#include "exceptdef.h"

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
  };

  template <class T, class Alloc>
  void vector<T, Alloc>::insert(iterator position, size_type n, const T &x)
  {
    if (n != 0)
    {
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
    }
  }

} // namespace tinystal

#endif // !TINYSTL_VECTOR_H_