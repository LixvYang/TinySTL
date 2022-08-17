#ifndef TINYSTL_ITERATOR_H_
#define TINYSTL_ITERATOR_H_

// 迭代器设计
// 这个头文件用于迭代器设计，包含了一些模板结构体与全局函数，
#include <cstddef>
#include "type_traits.h"

namespace tinystl
{
  // 五种迭代器类型
  struct input_iterator_tag
  {
  };
  struct output_iterator_tag
  {
  };
  struct forward_iterator_tag : public input_iterator_tag
  {
  };
  struct bidirectional_iterator_tag : public forward_iterator_tag
  {
  };
  struct random_access_iterator_tag : public bidirectional_iterator_tag
  {
  };

  // iterator 模板
  template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
  struct iterator
  {
    typedef Category iterator_category;
    typedef T value_type;
    typedef Pointer pointer;
    typedef Reference reference;
    typedef Distance difference_type;
  };

  // iterator traits
  template <class Iterator>
  struct iterator_traits
  {
    typedef typename Iterator::itearator_category itearator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
  };

  // 针对原生版本的* 偏特化版本
  template <class T>
  struct iterator_traits<T *>
  {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef ptrdiff_t difference_type;
  };

  template <class T>
  struct iterator_traits<const T *>
  {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef const T *pointer;
    typedef const T &reference;
    typedef ptrdiff_t difference_type;
  };

  // 萃取某个迭代器的category
  template <class Iterator>
  inline typename iterator_traits<Iterator>::iterator_category
  iterator_category(const Iterator &)
  {
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return category();
  }

  // 萃取某个迭代器的 distance_type
  template <class Iterator>
  inline typename iterator_traits<Iterator>::difference_type *
  distance_type(const Iterator &)
  {
    return static_cast<typename iterator_traits<Iterator>::difference_type *>(0);
  }

  // 萃取某个迭代器的 value_type
  template <class Iterator>
  typename iterator_traits<Iterator>::value_type *
  value_type(const Iterator &)
  {
    return static_cast<typename iterator_traits<Iterator>::value_type *>(0);
  }

  // 以下函数用于计算迭代器间的距离
  template <class InputIterator>
  typename iterator_traits<InputIterator>::difference_type
  __distance(InputIterator first, InputIterator last, input_iterator_tag)
  {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while (first != last)
    {
      ++first, ++n;
    }
    return n;
  }

  // distance 的 random_access_iterator_tag 的版本
  template <class RandomIter>
  typename iterator_traits<RandomIter>::difference_type
  __distance(RandomIter first, RandomIter last,
             random_access_iterator_tag)
  {
    return last - first;
  }

  template <class InputIterator>
  typename iterator_traits<InputIterator>::difference_type
  distance(InputIterator first, InputIterator last)
  {
    typedef typename iterator_traits<InputIterator>::itearator_category category;
    return __distance(first, last, category());
  }

  // 以下函数让迭代器前进n个距离
  // advance 的 input_iterator版本
  template <class InputIterator, class Distance>
  void __advance(InputIterator &i, Distance n, input_iterator_tag)
  {
    while (n--) ++i;
  }

  // advance 的 bidirectional_iterator_tag 的版本
  template <class BidirectionalIterator, class Distance>
  void __advance(BidirectionalIterator &i, Distance n, bidirectional_iterator_tag)
  {
    if (n >= 0)
      while (n--)
        ++i;
    else
      while (n++)
        --i;
  }

  // advance 的 random_access_iterator_tag 的版本
  template <class RandomIter, class Distance>
  void __advance(RandomIter &i, Distance n, random_access_iterator_tag)
  {
    i += n;
  }

  template <class InputIterator, class Distance>
  void advance(InputIterator &i, Distance n)
  {
    __advance(i, n, iterator_category(i));
  }

  /*
   *
  */

  // 模板类 : reverse_iterator
  // 代表反向迭代器，使前进为后退，后退为前进
  template <class Iterator>
  class reverse_iterator
  {
  private:
    Iterator current;

  public:
    typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
    typedef typename iterator_traits<Iterator>::value_type value_type;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Iterator>::pointer pointer;
    typedef typename iterator_traits<Iterator>::reference reference;

    typedef Iterator iterator_type;
    typedef reverse_iterator<Iterator> self;

  public:
    reverse_iterator() {}
    explicit reverse_iterator(iterator_type i) : current(i) {}
    reverse_iterator(const self &rhs) : current(rhs.current) {}

  public:
    iterator_type base() const { return current; }
    reference operator*() const
    {
      auto tmp = current;
      return *--tmp;
    }
    pointer operator->() const { return &(operator*()); }
    // 前进(++)变为后退(--)
    self &operator++()
    {
      --current;
      return *this;
    }
    self operator++(int)
    {
      self tmp = *this;
      --current;
      return tmp;
    }
    // 后退(--)变为前进(++)
    self &operator--()
    {
      ++current;
      return *this;
    }
    self operator--(int)
    {
      self tmp = *this;
      ++current;
      return tmp;
    }
    self &operator+=(difference_type n)
    {
      current -= n;
      return *this;
    }
    self operator+(difference_type n) const
    {
      return self(current - n);
    }
    self &operator-=(difference_type n)
    {
      current -= n;
      return *this;
    }
    self operator-(difference_type n) const
    {
      return self(current + n);
    }
    reference operator[](difference_type n) const
    {
      return *(*this + n);
    }
  };

  // 重载operator-
  template <class Iterator>
  typename reverse_iterator<Iterator>::difference_type
  operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
  {
    return rhs.base() - lhs.base();
  }

  // 重载比较运算符
  template <class Iterator>
  bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
  {
    return lhs.base() == rhs.base();
  }

  template <class Iterator>
  bool operator<(const reverse_iterator<Iterator> &lhs,
                 const reverse_iterator<Iterator> &rhs)
  {
    return rhs.base() < lhs.base();
  }

  template <class Iterator>
  bool operator!=(const reverse_iterator<Iterator> &lhs,
                  const reverse_iterator<Iterator> &rhs)
  {
    return !(lhs == rhs);
  }

  template <class Iterator>
  bool operator>(const reverse_iterator<Iterator> &lhs,
                 const reverse_iterator<Iterator> &rhs)
  {
    return rhs < lhs;
  }

  template <class Iterator>
  bool operator<=(const reverse_iterator<Iterator> &lhs,
                  const reverse_iterator<Iterator> &rhs)
  {
    return !(rhs < lhs);
  }

  template <class Iterator>
  bool operator>=(const reverse_iterator<Iterator> &lhs,
                  const reverse_iterator<Iterator> &rhs)
  {
    return !(lhs < rhs);
  }

}; // namespace tinystl

#endif // !TINYSTL_ITERATOR_H_