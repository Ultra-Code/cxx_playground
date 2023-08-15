#include <iostream>
#include <string_view>
#include <queue>
#include <memory>
#include <liberrors/errors.hxx>

namespace ds
{
  class tree
  {
    struct tree_node
    {
      std::string_view data_;
      std::unique_ptr<tree_node> left_, right_;
    };

    std::unique_ptr<tree_node> tree_;

    auto constexpr find(tree_node *root,
                        std::string_view position) const noexcept
        -> tree_node *
    {
      if (root == nullptr)
        {
          return nullptr;
        }
      if (root->data_ == position)
        {
          return root;
        }
      auto *first_found = find(root->left_.get(), position);
      if (first_found not_eq nullptr)
        {
          return first_found;
        }
      return find(root->right_.get(), position);
    }

  public:
    explicit tree(std::string_view position) noexcept
        : tree_{ std::make_unique<tree_node>(
            tree_node{ position, nullptr, nullptr }) }
    {
    }

    [[nodiscard]] auto
    root_node() const noexcept
    {
      return tree_.get();
    }

    [[nodiscard]] auto
    insert_subtree(std::string_view manager,
                   std::string_view subordinate) noexcept -> bool
    {
      auto *manager_node = find(root_node(), manager);
      errors::assert_that(manager_node not_eq nullptr,
                          "root manager node doesn't exist");
      if (manager_node->left_ && manager_node->right_)
        {
          return false;
        }
      if (manager_node->left_ == nullptr)
        {
          manager_node->left_ = std::make_unique<tree_node>(
              tree_node{ subordinate, nullptr, nullptr });
          return true;
        }
      if (manager_node->right_ == nullptr)
        {
          manager_node->right_ = std::make_unique<tree_node>(
              tree_node{ subordinate, nullptr, nullptr });
          return true;
        }
      return false;
    }

  };
} // namespace ds
