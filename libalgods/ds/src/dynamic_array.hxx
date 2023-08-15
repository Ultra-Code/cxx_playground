#pragma once
// module;
#include <cstddef>
#include <iterator>
#include <compare>
#include <memory>
#include <algorithm>
#include <initializer_list>
#include <utility>
#include <cassert>
#include <liberrors/errors.hxx>
// export module ds.dynamic_array;
// import<cstddef>;
// import<iterator>;
// import<compare>;
// import<memory>;
// import<algorithm>;
// import<initializer_list>;
// import<utility>;
// import<cassert>;

// export
namespace ds
{

  template<typename type> class dynamic_array
  {
    int64_t size_;
    int64_t capacity_;
    std::unique_ptr<type[]> data_; // NOLINT

    struct dyna_iter final
    {
      // member variables required by iterator_traits
      using difference_type = std::ptrdiff_t;
      using value_type = type;
      using pointer = type *;
      using const_pointer = type const *;
      using const_iterator = type const *;
      using reference = type &;
      using const_reference = type const &;
      using iterator_category = std::random_access_iterator_tag;
      using iterator_concept = std::contiguous_iterator_tag;

      // for ranges the iterator class needs to be default constructible
      explicit dyna_iter(pointer ptr = nullptr)
          : ptr_{ ptr }
      {
      }

      dyna_iter(dyna_iter const &copy) noexcept = default;

      auto
      operator=(dyna_iter const &copy) noexcept -> dyna_iter & = default;

      dyna_iter(dyna_iter &&move) noexcept = default;

      auto
      operator=(dyna_iter &&move) noexcept -> dyna_iter & = default;

      ~dyna_iter() = default;

      auto
      operator+=(difference_type const &diff) -> dyna_iter &
      {
        ptr_ += diff;
        return *this;
      }

      auto
      operator-=(difference_type const &diff) -> dyna_iter &
      {
        ptr_ -= diff;
        return *this;
      }

      // add two objects creates a new value which is local to the function so
      // must be returned by value
      auto
      operator+(difference_type const &diff) -> dyna_iter
      {
        auto old_ptr = ptr_;
        ptr_ = ptr_ + diff;
        auto temp = *this;
        ptr_ = old_ptr;
        return temp;
      }

      auto
      operator-(difference_type const &diff) -> dyna_iter
      {
        auto old_ptr = ptr_;
        ptr_ = ptr_ - diff;
        auto temp = *this;
        ptr_ = old_ptr;
        return temp;
      }

      auto
      operator++() -> dyna_iter &
      {
        ++ptr_;
        return *this;
      }

      auto
      operator--() -> dyna_iter &
      {
        --ptr_;
        return *this;
      }

      auto
      operator++(int) const -> dyna_iter
      {
        auto temp = *this;
        ++(*this);
        return temp;
      }

      auto
      operator--(int) const -> dyna_iter
      {
        auto temp = *this;
        --(*this);
        return temp;
      }

      auto
      operator*() const noexcept -> reference
      {
        return *ptr_;
      }

      auto
      operator->() const noexcept -> pointer
      {
        return ptr_;
      }

      auto
      operator<=>(dyna_iter const &rhs) const
          -> std::strong_ordering = default;

      auto
      operator==(dyna_iter const &rhs) const -> bool
          = default;

    private:
      pointer ptr_;
    };
    using iterator = dyna_iter;

    auto
    increase_dynamic_capacity(int64_t increase_rate) noexcept
    {
      errors::assert_that(increase_rate > 1,
                          "Error: increase_rate must be greater than one");

      auto bigger_array = dynamic_array(capacity_ * increase_rate);
      std::ranges::move(begin(), end(), bigger_array.begin());
      bigger_array.size_ = size_;
      *this = std::move(bigger_array);
    }

    [[nodiscard]] auto
    move_element_backward_for_insert(iterator pos) const noexcept -> size_t
    {
      const auto insert_position = std::ranges::distance(begin(), pos);
      const auto position_pos_to_size = size_ - insert_position;
      const auto position_pos_to_newsize = position_pos_to_size + 1;
      const auto pos_end = pos + position_pos_to_size;
      const auto insert_pos_end = pos + position_pos_to_newsize;
      std::ranges::move_backward(pos, pos_end, insert_pos_end);
      return insert_position;
    }

    auto
    insert_at(int64_t index, type const &value) noexcept
    {
      this->at(index) = value;
      size_++;
    }

  public:
    explicit dynamic_array(int64_t capacity)
        : size_{ 0 }
        , capacity_{ capacity } // NOLINTNEXTLINE
        , data_{ std::make_unique<type[]>(capacity) }
    {
    }
    // NOLINTNEXTLINE
    explicit dynamic_array(std::initializer_list<type> &&list)
        : size_{ int64_t(list.size()) }
        , capacity_{ int64_t(list.size()) }
        , data_{ std::make_unique<type[]>(list.size()) } // NOLINT
    {
      std::ranges::move(list, begin());
    }

    dynamic_array(dynamic_array const &copy)
        : size_{ copy.size_ }
        , capacity_{ copy.size_ }
        , data_{ std::make_unique<type[]>(size_) } // NOLINT
    {
      std::ranges::copy(copy.begin(), copy.end(), begin());
    }

    dynamic_array(dynamic_array &&move) noexcept
        : size_{ std::exchange(move.size_, 0) }
        , capacity_{ std::exchange(move.capacity_, 0) }
        , data_{ std::exchange(move.data_, nullptr) }
    {
    }

    auto
    operator=(dynamic_array const &copy) -> dynamic_array &
    {
      if (&copy != this)
        {
          auto copied = dynamic_array(copy);
          this->swap(copied);
        }
      return *this;
    }

    auto
    operator=(dynamic_array &&move) noexcept -> dynamic_array &
    {
      auto moved = std::move(move);
      this->swap(moved);
      return *this;
    }

    [[nodiscard]] auto
    at(int64_t index) const noexcept -> type &
    {
      errors::assert_that(index <= size_ and index >= 0,
                          "Error: index out of range");
      return this->data_[index];
    }

    auto
    push_back(type const &value) noexcept -> void
    {
      if (size_ < capacity_)
        {
          auto const index = size_;
          insert_at(index, value);
        }
      else
        {
          increase_dynamic_capacity(2);
          auto const index = size_;
          insert_at(index, value);
        }
    }

    auto
    pop_back() noexcept -> void
    {
      *end() = 0;
      --size_;
    }

    auto
    insert(iterator pos, type const &value) noexcept
    {
      const auto position = std::ranges::distance(begin(), pos);
      errors::assert_that(position <= size_ and position >= 0,
                          "Error: inserting out of bound");
      if (size_ < capacity_)
        {
          if (position < size_)
            {
              auto insert_index = move_element_backward_for_insert(pos);
              insert_at(insert_index, value);
            }
          else if (position == size_)
            {
              const auto insert_index = position;
              insert_at(insert_index, value);
            }
        }
      else if (capacity_ == size_)
        {
          if (position < size_)
            {
              // after this operation previous iterators are invalidated
              // and must be reseted before used
              increase_dynamic_capacity(2);
              pos = begin() + position;
              auto insert_index = move_element_backward_for_insert(pos);
              insert_at(insert_index, value);
            }
          else if (position == size_)
            {
              increase_dynamic_capacity(2);
              auto const insert_index = position;
              insert_at(insert_index, value);
            }
        }
    }

    auto
    swap(dynamic_array &rhs) noexcept -> void
    {
      std::swap(rhs.data_, data_);
      std::swap(rhs.capacity_, capacity_);
      std::swap(rhs.size_, size_);
    }

    [[nodiscard]] auto
    operator[](size_t index) noexcept -> type &
    {
      assert(index < size_
             && "index must not be equal or greater than size of array");
      return data_[index];
    }

    [[nodiscard]] auto
    size() const -> size_t
    {
      return size_;
    }

    [[nodiscard]] auto
    capacity() const -> size_t
    {
      return capacity_;
    }

    auto
    begin() const noexcept -> iterator
    {
      return dyna_iter(data_.get());
    }

    auto
    end() const noexcept -> iterator
    {
      return dyna_iter(data_.get() + size_);
    }

    auto
    begin() noexcept -> iterator
    {
      return dyna_iter(data_.get());
    }

    auto
    end() noexcept -> iterator
    {
      return dyna_iter(data_.get() + size_);
    }

    ~dynamic_array() = default;
  };

  template<typename type>
  auto
  swap(dynamic_array<type> const &lhs, dynamic_array<type> const &rhs) noexcept
      -> void
  {
    lhs.swap(rhs);
  }

} // namespace ds
