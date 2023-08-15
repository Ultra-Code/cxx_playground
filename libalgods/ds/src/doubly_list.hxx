#pragma once
// module;
#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <algorithm>
// export module ds.doubly_list;
// import<cstddef>;
// import <algorithm>;
// import<iterator>;
// import<iostream>;
// import<memory>;

// export
namespace ds
{
  template<typename type> class doubly_list final
  {

    struct doubly_list_node
    {
      type value_;
      std::shared_ptr<doubly_list_node> next_;
      doubly_list_node *previous_;
    };

    using node = doubly_list_node;
    using head_ptr = std::shared_ptr<node>;
    using tail_ptr = std::shared_ptr<node>;

    size_t list_size_{};
    head_ptr head_{};
    tail_ptr tail_{};

    struct doubly_list_itr
    {
      using difference_type = std::ptrdiff_t;
      using value_type = type;
      using pointer = node *;
      using reference = node &;
      using iterator_concept = std::bidirectional_iterator_tag;
      using iterator_category = std::bidirectional_iterator_tag;

      explicit doubly_list_itr(pointer ptr = nullptr) noexcept
          : ptr_{ ptr }
      {
      }

      auto
      operator*() const noexcept -> value_type
      {
        return ptr_->value_;
      }

      auto
      operator->() const noexcept -> pointer
      {
        return ptr_;
      }

      auto
      ptr() const noexcept -> pointer
      {
        return ptr_;
      }

      auto
      operator++() noexcept -> doubly_list_itr &
      {
        ptr_ = ptr_->next_.get();
        return *this;
      }

      auto
      operator--() noexcept -> doubly_list_itr &
      {
        ptr_ = ptr_->previous_;
        return *this;
      }

      auto
      operator++(int) const noexcept -> doubly_list_itr
      {
        auto temp = *this;
        ++(*this);
        return temp;
      }

      auto
      operator--(int) const noexcept -> doubly_list_itr
      {
        auto temp = *this;
        --(*this);
        return temp;
      }

      auto
      operator<=>(doubly_list_itr const &rhs) const noexcept
          -> std::strong_ordering = default;

      auto
      operator==(doubly_list_itr const &rhs) const noexcept -> bool
          = default;

    private:
      pointer ptr_;
    };

    using iterator = doubly_list_itr;

  public:
    doubly_list() noexcept
        : tail_{ std::make_shared<node>() }
    {
    }

    // NOLINTNEXTLINE
    explicit doubly_list(std::initializer_list<type> list)
        : doubly_list()
    {
      for (auto const &element : list)
        {
          push_back(element);
        }
    }

    auto
    push_front(type const &value) noexcept -> void
    {
      insert(begin(), value);
    }

    auto
    push_back(type const &value) noexcept -> void
    {
      auto constexpr zero = uint(0);
      auto current_end = end();
      size() == zero ? push_front(value) : insert(current_end, value);
    }

    auto
    insert(iterator position, type const &value) noexcept -> void
    {
      auto new_node = std::make_shared<node>(value);

      if (position == begin())
        {
          auto constexpr zero = uint(0);
          if (size() == zero)
            {
              head_ = new_node;
              head_->next_ = tail_;
              head_->previous_ = end().ptr();
              tail_->previous_ = begin().ptr();
            }
          else if (size() > zero)
            {
              new_node->next_ = head_;
              new_node->previous_ = head_->previous_;
              head_->previous_ = new_node.get();
              head_ = new_node;
            }
        }
      else if (position == end())
        {
          new_node->next_ = tail_;
          new_node->previous_ = tail_->previous_;
          tail_->previous_->next_ = new_node;
          tail_->previous_ = new_node.get();
        }
      else
        {
          auto current_begin = begin();
          auto const distance = std::ranges::distance(current_begin, position);
          auto const half_range = std::floor(size() / 2);
          if (distance <= half_range)
            {
              auto constexpr insert_offset = uint8_t(1);
              auto const forward_distance = distance - insert_offset;
              auto foward_insert_position
                  = std::ranges::next(current_begin, forward_distance);
              new_node->next_ = foward_insert_position->next_;
              new_node->previous_ = foward_insert_position.ptr();
              foward_insert_position->next_->previous_ = new_node.get();
              foward_insert_position->next_ = new_node;
            }
          else
            {
              auto current_end = end();
              auto const backward_distance = size() - distance;
              auto backward_insert_position
                  = std::ranges::prev(current_end, backward_distance);
              new_node->next_ = backward_insert_position->previous_->next_;
              new_node->previous_ = backward_insert_position->previous_;
              backward_insert_position->previous_->next_ = new_node;
              backward_insert_position->previous_ = new_node.get();
            }
        }
      ++list_size_;
    }

    auto
    pop_front() noexcept -> void
    {
      auto new_head = head_->next_;
      [[maybe_unused]] auto old_head = std::move(head_);
      head_ = std::move(new_head);
      --list_size_;
    }

    auto
    pop_back() noexcept -> void
    {
      auto new_tail = tail_->previous_->previous_->next_;
      [[maybe_unused]] auto old_tail = std::move(tail_);
      tail_ = std::move(new_tail);
      --list_size_;
    }

    auto
    find(type const &value) const -> iterator
    {
      return std::ranges::find(begin(), end(), value);
    }

    auto
    remove(type const &value) noexcept -> void
    {
      auto remove_position = find(value);
      if (remove_position not_eq end())
        {
          if (size() > 1UL)
            {
              [[maybe_unused]] auto element_to_remove
                  = std::move(remove_position->previous_->next_);
              remove_position->next_->previous_ = remove_position->previous_;
              remove_position->previous_->next_ = remove_position->next_;
            }
          else
            {
              [[maybe_unused]] auto element_to_remove
                  = std::move(remove_position->previous_->next_);
            }
        }
      --list_size_;
    }

    auto
    clear() noexcept -> void
    {
      for (auto const &values : *this)
        {
          remove(values);
        }
    }

    [[nodiscard]] auto
    empty() const noexcept -> bool
    {
      return size() == 0UL;
    }

    [[nodiscard]] auto
    size() const noexcept -> size_t
    {
      return list_size_;
    }

    auto
    begin() const noexcept -> iterator
    {
      return iterator{ head_.get() };
    }

    auto
    end() const noexcept -> iterator
    {
      return iterator{ tail_.get() };
    }
  };
} // namespace ds
