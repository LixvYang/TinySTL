#ifndef TINYSTL_LIST_H_
#define TINYSTL_LIST_H_

#include <initializer_list>
#include "allocator.h"
#include "iterator.h"
#include "memory.h"
#include "utils.h"
#include "exceptdef.h"

namespace tinystl
{
  template <class T>
  struct list_node;
  template <class T>
  struct list_node_base;

  template <class T>
  struct node_traits
  {
    typedef list_node_base<T> *base_ptr;
    typedef list_node<T> *node_ptr;
  };

  // list 节点struct
  template <class T>
  struct list_node_base
  {
    typedef typename node_traits<T>::base_ptr base_ptr;
    typedef typename node_traits<T>::node_ptr node_ptr;

    base_ptr prev;
    base_ptr next;

    list_node_base() = default;
    node_ptr as_node()
    {
      return static_cast<node_ptr>(self());
    }

    void unlink()
    {
      prev = next = self();
    }

    base_ptr self()
    {
      return static_cast<base_ptr>(&*this);
    }
  };

  template <class T>
  struct list_node : public list_node_base<T>
  {
    typedef typename node_traits<T>::base_ptr base_ptr;
    typedef typename node_traits<T>::node_ptr node_ptr;

    T value;

    list_node() = default;
    list_node(const T &v) : value(v) {}
    list_node(T &&v) : value(tinystl::move(v)) {}
    base_ptr as_base() { return static_cast<base_ptr>(&*this); }
    node_ptr self() { return static_cast<T>(&*this); }
  };

  // list 迭代器
  template <class T>
  struct list_iterator : public tinystl::iterator<tinystl::bidirectional_iterator_tag, T>
  {
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef typename node_traits<T>::base_ptr base_ptr;
    typedef typename node_traits<T>::node_ptr node_ptr;
    typedef list_iterator<T> self;

    base_ptr node_;

    // 构造函数
    list_iterator() = default;
    list_iterator(base_ptr x) : node_(x) {}
    list_iterator(node_ptr x) : node_(x->as_base()) {}
    list_iterator(const list_iterator &rhs) : node_(rhs.node_) {}

    // 重载操作符
    reference operator*() const { return node_->as_node()->value; }
    pointer operator->() const { return &(operator*()); }

    self &operator++()
    {
      MYSTL_DEBUG(node_ != nullptr);
      node_ = node_->next;
      return *this;
    }
    self operator++(int)
    {
      self tmp = *this;
      ++*this;
      return tmp;
    }
    self &operator--()
    {
      MYSTL_DEBUG(node_ != nullptr);
      node_ = node_->prev;
      return *this;
    }
    self operator--(int)
    {
      self tmp = *this;
      --*this;
      return tmp;
    }

    bool operator==(const self &rhs) const { return node_ == rhs.node_; }
    bool operator!=(const self &rhs) const { return node_ != rhs.node_; }
  };

  template <class T>
  struct list_const_iterator : public iterator<bidirectional_iterator_tag, T>
  {
    typedef T value_type;
    typedef const T *pointer;
    typedef const T &reference;
    typedef typename node_traits<T>::base_ptr base_ptr;
    typedef typename node_traits<T>::node_ptr node_ptr;
    typedef list_const_iterator<T> self;

    base_ptr node_;

    list_const_iterator() = default;
    list_const_iterator(base_ptr x)
        : node_(x) {}
    list_const_iterator(node_ptr x)
        : node_(x->as_base()) {}
    list_const_iterator(const list_iterator<T> &rhs)
        : node_(rhs.node_) {}
    list_const_iterator(const list_const_iterator &rhs)
        : node_(rhs.node_) {}

    reference operator*() const { return node_->as_node()->value; }
    pointer operator->() const { return &(operator*()); }

    self &operator++()
    {
      MYSTL_DEBUG(node_ != nullptr);
      node_ = node_->next;
      return *this;
    }
    self operator++(int)
    {
      self tmp = *this;
      ++*this;
      return tmp;
    }
    self &operator--()
    {
      MYSTL_DEBUG(node_ != nullptr);
      node_ = node_->prev;
      return *this;
    }
    self operator--(int)
    {
      self tmp = *this;
      --*this;
      return tmp;
    }

    // 重载比较操作符
    bool operator==(const self &rhs) const { return node_ == rhs.node_; }
    bool operator!=(const self &rhs) const { return node_ != rhs.node_; }
  };

  // list
  template <class T>
  class list
  {
  public:
    typedef tinystl::allocator<T> allocator_type;
    typedef tinystl::allocator<T> data_allocator;
    typedef tinystl::allocator<list_node_base<T>> base_allocator;
    typedef tinystl::allocator<list_node<T>> node_allocator;

    typedef typename allocator_type::value_type value_type;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;

    typedef list_iterator<T> iterator;
    typedef list_const_iterator<T> const_iterator;
    typedef tinystl::reverse_iterator<iterator> reverse_iterator;
    typedef tinystl::reverse_iterator<const_iterator> const_reverse_iterator;

    typedef typename node_traits<T>::base_ptr base_ptr;
    typedef typename node_traits<T>::node_ptr node_ptr;

    allocator_type get_allocator()
    {
      return node_allocator();
    }

  private:
    base_ptr node_;
    size_type size_;

  public:
    // 构造、复制、移动、析构函数
    list() { fill_init(0, value_type()); }
    explicit list(size_type n) { fill_init(n, value_type()); }
    list(size_type n, const T &value) { fill_init(n, value); }
    template <class Iter, typename std::enable_if<
                              tinystl::is_input_iterator<Iter>::value, int>::type = 0>
    list(Iter first, Iter last)
    {
      copy_init(first, last);
    }

    list(std::initializer_list<T> ilist) { copy_init(ilist.begin(), ilist.end()); }
    list(const list &rhs) { copy_init(rhs.cbegin(), rhs.cend()); }

    list(list &&rhs) noexcept : node_(rhs.node_), size_(rhs.size_)
    {
      rhs.node_ = nullptr;
      rhs.size_ = 0;
    }

    list &operator=(const list &rhs)
    {
      if (this != &rhs)
      {
        assign(rhs.begin(), rhs.end());
      }
      return *this;
    }

    list &operator=(list &&rhs) noexcept
    {
      clear();
      splice(end(), rhs);
      return *this;
    }

    list &operator=(std::initializer_list<T> ilist)
    {
      list tmp(ilist.begin(), ilist.end());
      swap(tmp);
      return *this;
    }

    ~list()
    {
      if (node_)
      {
        clear();
        base_allocator::deallocate(node_);
        node_ = nullptr;
        size_ = 0;
      }
    }

  public:
    iterator begin() noexcept { return node_->next; }
    const_iterator begin() const noexcept { return node_->next; }
    iterator end() noexcept { return node_; }
    const_iterator end() const noexcept { return node_; }
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }\
    

  private:
    // helper functioon
    // create / destory node
    template <class... Args>
    node_ptr
    create_node(Args &&...args);
    void destory_node(node_ptr p);

    // initialize
    void fill_init(size_type n, const value_type &value);
    template <class Iter>
    void copy_init(Iter first, Iter last);

    // link / unlinnk
    iterator link_iter_node(const_iterator pos, base_ptr node);
    void link_nodes(base_ptr p, base_ptr first, base_ptr last);
    void link_nodes_at_front(base_ptr first, base_ptr last);
    void link_nodes_at_back(base_ptr first, base_ptr last);
    void unlink_nodes(base_ptr f, base_ptr l);

    // asign;
    void fill_assign(size_type n, const value_type &value);
    template <class Iter>
    void copy_asign(Iter first, Iter last);

    // insert
    iterator fill_insert(const_iterator pos, size_type n, const value_type &value);
    template <class Iter>
    iterator copy_insert(const_iterator pos, size_type n, Iter first);

    // sort
    template <class Compared>
    iterator list_sort(iterator first, iterator last, size_type n, Compared comp);
  };
}
#endif // TINYSTL_LIST_H_
