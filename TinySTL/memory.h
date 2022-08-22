#ifndef TINYSTL_MEMORY_H_
#define TINYSTL_MEMORY_H_

namespace tinystl
{
  template <class Tp>
  constexpr Tp *address_of(Tp &value) noexcept
  {
    return &value;
  }
} // namespace tinystal

#endif // TINYSTL_MEMORY_H_
