#ifndef TINYSTL_QUEUE_H_
#define TINYSTL_QUEUE_H_

#include "deque.h"
#include "vector.h"

namespace tinystl
{
  template <class T, class Container = tinystl::deque<T>>
  class queue
  {
  public:
    typedef Container container_type;
    // 使用底层容器的型别
    typedef typename Container::value_type value_type;
    typedef typename Container::size_type size_type;
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;

    static_assert(std::is_same<T, value_type>::value,
                  "the value_type of Container should be same with T");

  private:
    container_type c_;

  public:
    queue() = default;

    explicit queue(size_type n)
        : c_(n)
    {
    }
    queue(size_type n, const value_type &value)
        : c_(n, value)
    {
    }

    template <class IIter>
    queue(IIter first, IIter last)
        : c_(first, last)
    {
    }

    queue(std::initializer_list<T> ilist)
        : c_(ilist.begin(), ilist.end())
    {
    }

    queue(const Container &c)
        : c_(c)
    {
    }
    queue(Container &&c) noexcept(std::is_nothrow_move_constructible<Container>::value)
        : c_(tinystl::move(c))
    {
    }

    queue(const queue &rhs)
        : c_(rhs.c_)
    {
    }
    queue(queue &&rhs) noexcept(std::is_nothrow_move_constructible<Container>::value)
        : c_(tinystl::move(rhs.c_))
    {
    }

    queue &operator=(const queue &rhs)
    {
      c_ = rhs.c_;
      return *this;
    }
    queue &operator=(queue &&rhs) noexcept(std::is_nothrow_move_assignable<Container>::value)
    {
      c_ = tinystl::move(rhs.c_);
      return *this;
    }

    queue &operator=(std::initializer_list<T> ilist)
    {
      c_ = ilist;
      return *this;
    }

    ~queue() = default;

    // 访问元素相关操作
    reference front() { return c_.front(); }
    const_reference front() const { return c_.front(); }
    reference back() { return c_.back(); }
    const_reference back() const { return c_.back(); }

    // 容量相关操作
    bool empty() const noexcept { return c_.empty(); }
    size_type size() const noexcept { return c_.size(); }

    // 修改容器相关操作
    template <class... Args>
    void emplace(Args &&...args)
    {
      c_.emplace_back(tinystl::forward<Args>(args)...);
    }

    void push(const value_type &value)
    {
      c_.push_back(value);
    }
    void push(value_type &&value)
    {
      c_.emplace_back(tinystl::move(value));
    }

    void pop()
    {
      c_.pop_front();
    }

    void clear()
    {
      while (!empty())
        pop();
    }

    void swap(queue &rhs) noexcept(noexcept(tinystl::swap(c_, rhs.c_)))
    {
      tinystl::swap(c_, rhs.c_);
    }

  public:
    friend bool operator==(const queue &lhs, const queue &rhs) { return lhs.c_ == rhs.c_; }
    friend bool operator<(const queue &lhs, const queue &rhs) { return lhs.c_ < rhs.c_; }
  };

  // 重载比较操作符
  template <class T, class Container>
  bool operator==(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
  {
    return lhs == rhs;
  }

  template <class T, class Container>
  bool operator!=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
  {
    return !(lhs == rhs);
  }

  template <class T, class Container>
  bool operator<(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
  {
    return lhs < rhs;
  }

  template <class T, class Container>
  bool operator>(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
  {
    return rhs < lhs;
  }

  template <class T, class Container>
  bool operator<=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
  {
    return !(rhs < lhs);
  }

  template <class T, class Container>
  bool operator>=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
  {
    return !(lhs < rhs);
  }

  // 重载 tinystl 的 swap
  template <class T, class Container>
  void swap(queue<T, Container> &lhs, queue<T, Container> &rhs) noexcept(noexcept(lhs.swap(rhs)))
  {
    lhs.swap(rhs);
  }

} // namespace tinystl

#endif // !TINYSTL_QUEUE_H_