#pragma once
// module;
#include <cstddef>          // for ptrdiff_t
#include <iterator>         // forward_iterator_tag
#include <memory>           // shared_ptr
#include <compare>          // strong_ordering
#include <initializer_list> // initializer_list
#include <algorithm>
// export module ds.singly_list;
// import<cstddef>;
// import<iterator>;
// import<memory>;
// import<compare>;
// import<initializer_list>;
// import<algorithm>;

// export
namespace ds
{
  template<typename type> class singly_list
  {
    struct singly_node
    {
      type value_;
      std::shared_ptr<singly_node> next_;
    };

    using node = singly_node;
    using node_ptr = std::shared_ptr<singly_node>;
    node_ptr head_ = nullptr;

    struct singly_iter
    {
      using difference_type = std::ptrdiff_t;
      using value_type = node;
      using pointer = node *;
      using reference = node &;
      using iterator_concept = std::forward_iterator_tag;
      using iterator_category = std::forward_iterator_tag;

      explicit singly_iter(pointer ptr = nullptr) noexcept
          : ptr_{ ptr }
      {
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
      operator++() noexcept -> singly_iter &
      {
        ptr_ = ptr_->next_.get();
        return *this;
      }

      auto
      operator++(int) const noexcept -> singly_iter
      {
        auto temp = *this;
        ++(*this);
        return temp;
      }

      auto
      operator<=>(singly_iter const &rhs) const noexcept
          -> std::strong_ordering = default;

      auto
      operator==(singly_iter const &rhs) const noexcept -> bool
          = default;

    private:
      pointer ptr_;
    };

    using iterator = singly_iter;

  public:
    singly_list() = default;

    // NOLINTNEXTLINE
    explicit singly_list(std::initializer_list<type> list)
    {
      std::ranges::for_each(
          std::ranges::rbegin(list), std::ranges::rend(list),
          [this](auto const &element) { push_front(element); });
    }

    singly_list(singly_list const &rhs) noexcept
        : head_{ rhs.head_ ? std::make_shared<node>(rhs.head_->value_)
                           : nullptr }
    {
      assert_that(rhs.head_ not_eq nullptr, "can't copy an empty list");
      std::ranges::copy(rhs, begin());
    }

    auto
    operator=(singly_list const &copy) -> singly_list &
    {
      if (this != &copy)
        {
          *this = copy;
        }
      return *this;
    }

    singly_list(singly_list &&move) noexcept
        : head_{ std::exchange(move.head_, nullptr) }
    {
    }

    auto
    operator=(singly_list &&move) noexcept -> singly_list &
    {
      head_ = std::move(move);
      return *this;
    }

    ~singly_list() = default;

    auto
    push_front(type value) noexcept -> void
    {
      auto new_node = std::make_shared<node>(std::move(value));
      if (head_ not_eq nullptr)
        {
          new_node->next_ = head_;
        }
      head_ = new_node;
    }

    auto
    pop_front() noexcept -> void
    {
      assert_that(head_ not_eq nullptr,
                  "Can't remove the front element when the list is empty");
      auto new_head = std::move(head_->next_);
      [[maybe_unused]] auto old_head = std::move(head_);
      head_ = new_head;
    }

    auto
    begin() const noexcept -> iterator
    {
      return singly_iter{ head_.get() };
    }

    static auto
    end() noexcept -> iterator
    {
      return singly_iter{ nullptr };
    }

    static auto
    value(node const &node) noexcept -> type
    {
      return node.value_;
    }
  };

  template<typename type>
  auto
  operator<<(std::ostream &stream, singly_list<type> const &list)
      -> std::ostream &
  {
    for (auto const &element : list)
      {
        stream << singly_list<type>::value(element) << ' ';
      }
    return stream;
  }
} // namespace ds
