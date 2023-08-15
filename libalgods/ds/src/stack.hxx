#pragma once
// module;
#include <cstddef>
#include <initializer_list>
#include <src/dynamic_array.hxx>
// export module ds.stack;
// import ds.dynamic_array;
// import<cstddef>;
// import<initializer_list>;

// export
namespace stack
{
  template<typename type> class stack
  {
    ds::dynamic_array<type> array_;

    // NOLINTNEXTLINE
    explicit stack(std::initializer_list<type> list) noexcept
        : array_{ list.begin(), list.end() }
    {
    }

    explicit stack(size_t capacity = 4) noexcept
        : array_{ capacity }
    {
    }

  public:
    [[nodiscard]] auto
    empty() const noexcept -> bool
    {
      return array_.size() == 0;
    }

    [[nodiscard]] auto
    size() const noexcept -> size_t
    {
      return array_.size();
    }

    auto
    top() const noexcept -> type &
    {
      return *array_.end();
    }

    auto
    push(type const &value) noexcept -> void
    {
      array_.push_back(value);
    }

    auto
    pop() noexcept -> void
    {
      array_.pop_back();
    }

    auto
    begin() const noexcept -> void
    {
      array_.begin();
    }

    auto
    end() const noexcept -> void
    {
      array_.end();
    }
  };
} // namespace stack
