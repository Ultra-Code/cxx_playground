#include <iostream>
#include <liberrors/errors.hxx>
#include <memory>
#include <queue>

namespace ds {
class bsearch_tree {
  struct tree_node {
    int node_value_;
    std::unique_ptr<tree_node> left_, right_;
  };
  std::unique_ptr<tree_node> root_;

  [[nodiscard]] auto find_subtree(tree_node *current,
                                  int node_value) const noexcept
      -> tree_node * {

    if (current == nullptr) {
      return nullptr;
    }
    if (current->node_value_ == node_value) {
      return current;
    }
    if (node_value < current->node_value_) {
      return find_subtree(current->left_.get(), node_value);
    }
    // if (node_value > current->node_value_)
    return find_subtree(current->right_.get(), node_value);
  }

  auto insert_subtree(tree_node *current, int node_value) noexcept -> bool {
    errors::assert_that(find(node_value) == nullptr,
                        "a node with this value already exist");
    if (node_value < current->node_value_) {
      if (current->left_ not_eq nullptr) {
        insert_subtree(current->left_.get(), node_value);
      } else {
        current->left_ = std::make_unique<tree_node>(
            tree_node{node_value, nullptr, nullptr});
        return true;
      }
    } else if (node_value > current->node_value_) {
      if (current->right_ not_eq nullptr) {
        insert_subtree(current->right_.get(), node_value);
      } else {
        current->right_ = std::make_unique<tree_node>(
            tree_node{node_value, nullptr, nullptr});
        return true;
      }
    }
    return false;
  }

public:
  explicit bsearch_tree(int root_id) noexcept
      : root_{std::make_unique<tree_node>(
            tree_node{root_id, nullptr, nullptr})} {}

  [[nodiscard]] auto root_node() const noexcept { return root_.get(); }

  [[nodiscard]] auto find(int node_value) const noexcept -> tree_node * {
    return find_subtree(root_node(), node_value);
  }

  auto insert(int node_value) noexcept {
    return insert_subtree(root_node(), node_value);
  }

  static auto successor(tree_node *root) noexcept -> tree_node * {
    auto *potential_successor = root->right_.get();
    while (potential_successor->left_ not_eq nullptr) {
      potential_successor = potential_successor->left_.get();
    }
    return potential_successor;
  }

  static auto level_order_traversal(tree_node *node) noexcept {
    if (node == nullptr) {
      return;
    }
    auto level_queue = std::queue<tree_node *>({node});
    while (not level_queue.empty()) {
      auto size = level_queue.size();
      for (size_t i = 0; i < size; i++) {
        auto *current_level = level_queue.front();
        level_queue.pop();
        std::cout << current_level->node_value_ << ", ";
        if (current_level->left_ not_eq nullptr) {
          level_queue.push(current_level->left_.get());
        }
        if (current_level->right_ not_eq nullptr) {
          level_queue.push(current_level->right_.get());
        }
      }
      std::cout << '\n';
    }
  }

  // TODO(ultracode): fix but and add successor functin
#if 0
    auto
    remove_subtree(tree_node *current, int node_value) const noexcept -> tree_node*
    {
      if (current == nullptr)
        {
          return nullptr;
        }
      if (node_value < current->node_value_)
        {
          current->left_ = remove_subtree(current->left_.get(), node_value);
        }
      else if (node_value > current->node_value_)
        {
          current->right_ = remove_subtree(current->right_.get(), node_value);
        }
      else
        {
          if (current->left_ == nullptr and current->right_ == nullptr)
            {
              auto delete_node = std::unique_ptr<tree_node>(current);
              delete_node.reset(nullptr);
            }
          else if (current->left_ == nullptr)
            {
              auto *temp_current = current;
              current = current->right_.get();
              auto delete_node = std::unique_ptr<tree_node>(temp_current);
              delete_node.reset(nullptr);
            }
          else if (current->right_ == nullptr)
            {
              auto *temp_current = current;
              current = current->left_.get();
              auto delete_node = std::unique_ptr<tree_node>(temp_current);
              delete_node.reset(nullptr);
            }
          else
            {
              auto *successor_node = successor(root_node());
              current->node_value_ = successor_node->node_value_;
              current->right_ = remove_subtree(current->right_.get(),node_value);
            }
        }
        // return current;
    }
#endif
};
} // namespace ds
