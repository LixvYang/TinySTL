#ifndef TINYSTL_RB_TREE_H_
#define TINYSTL_RB_TREE_H_

#include <initializer_list>

#include <cassert>
#include "iterator.h"
#include "memory.h"
#include "type_traits.h"
#include "exceptdef.h"

namespace tinystl
{
  // rb tree 节点颜色的类型
  typedef bool rb_tree_color_type;
  static constexpr rb_tree_color_type rb_tree_red = false;
  static constexpr rb_tree_color_type rb_tree_black = true;

  // forward declaration
  template <class T>
  struct rb_tree_node_base;
  template <class T>
  struct rb_tree_node;

  template <class T>
  struct rb_tree_iterator;
  template <class T>
  struct rb_tree_const_iterator;

  // rb tree value traits
  template <class T, bool>
  struct rb_tree_value_traits_imp
  {
    typedef T key_type;
    typedef T mapped_type;
    typedef T value_type;

    template <class Ty>
    static const key_type &get_key(const Ty &value)
    {
      return value;
    }
    template <class Ty>
    static const value_type &get_value(const Ty &value)
    {
      return value;
    }
  };

  template <class T>
  struct rb_tree_value_traits_imp<T, true>
  {
    typedef typename std::remove_cv<typename T::first_type>::type key_type;
    typedef typename T::second_type mapped_type;
    typedef T value_type;

    template <class Ty>
    static const key_type &get_key(const Ty &value)
    {
      return value.first;
    }

    template <class Ty>
    static const value_type &get_value(const Ty &value)
    {
      return value;
    }
  };

  template <class T>
  struct rb_tree_value_traits
  {
    static constexpr bool is_map = tinystl::is_pair<T>::value;
    typedef rb_tree_value_traits_imp<T, is_map> value_traits_type;
    typedef typename value_traits_type::key_type key_type;
    typedef typename value_traits_type::mapped_type mapped_type;
    typedef typename value_traits_type::value_type value_type;

    template <class Ty>
    static const key_type &get_key(const Ty &value)
    {
      return value_traits_type::get_key(value);
    }

    template <class Ty>
    static const key_type &get_value(const Ty &value)
    {
      return value_traits_type::get_value(value);
    }
  };

  // rb tree node traits
  template <class T>
  struct rb_tree_node_traits
  {
    typedef rb_tree_color_type color_type;
    typedef rb_tree_value_traits<T> value_traits;
    typedef typename value_traits::key_type key_type;
    typedef typename value_traits::mapped_type mapped_type;
    typedef typename value_traits::value_type value_type;

    typedef rb_tree_node_base<T> *base_ptr;
    typedef rb_tree_node<T> *node_ptr;
  };

  // rb tree 的节点设计
  template <class T>
  struct rb_tree_node_base
  {
    typedef rb_tree_color_type color_type;
    typedef rb_tree_node_base<T> *base_ptr;
    typedef rb_tree_node<T> *node_ptr;

    base_ptr parent;
    base_ptr left;
    base_ptr right;
    color_type color;

    base_ptr get_base_ptr()
    {
      return &*this;
    }

    node_ptr get_node_ptr()
    {
      return reinterpret_cast<node_ptr>(&*this);
    }

    node_ptr &get_node_ref()
    {
      return reinterpret_cast<node_ptr &>(*this);
    }
  };

  template <class T>
  struct rb_tree_node : public rb_tree_node_base<T>
  {
    typedef rb_tree_node_base<T> *base_ptr;
    typedef rb_tree_node<T> *node_ptr;

    T value; // 节点值

    base_ptr get_base_ptr()
    {
      return static_cast<base_ptr>(&*this);
    }

    node_ptr get_node_ptr()
    {
      return &*this;
    }
  };

  // rb tree traits

  template <class T>
  struct rb_tree_traits
  {
    typedef rb_tree_value_traits<T> value_traits;

    typedef typename value_traits::key_type key_type;
    typedef typename value_traits::mapped_type mapped_type;
    typedef typename value_traits::value_type value_type;

    typedef value_type *pointer;
    typedef value_type &reference;
    typedef const value_type *const_pointer;
    typedef const value_type &const_reference;

    typedef rb_tree_node_base<T> base_type;
    typedef rb_tree_node<T> node_type;

    typedef base_type *base_ptr;
    typedef node_type *node_ptr;
  };

  
} // namespace tinystl

#endif // !TINYSTL_RB_TREE_H_